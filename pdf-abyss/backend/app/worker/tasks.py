import os
import tempfile
from datetime import datetime

from sqlalchemy import select

from app.core.config import settings
from app.core.utils import sanitize_filename
from app.db.session import SessionLocal
from app.models import (
    File as FileModel,
    FileStatus,
    ScanStatus,
    ScanReport,
    Category,
)
from app.services import scanning, storage, classification
from app.worker.celery_app import celery_app


@celery_app.task(bind=True)
def scan_and_publish_file(self, file_id: int):
    db = SessionLocal()

    try:
        db_file = db.get(FileModel, file_id)

        if not db_file:
            return

        db_file.status = FileStatus.scanning
        db_file.scan_status = ScanStatus.scanning
        db.commit()

        with tempfile.TemporaryDirectory() as tmp_dir:
            local_path = os.path.join(tmp_dir, "upload.pdf")

            storage.download_file(
                bucket_name=settings.quarantine_bucket,
                key=db_file.quarantine_key,
                local_path=local_path,
            )

            clam_result = scanning.clamav_scan(local_path)
            pdf_result = scanning.pdf_structure_scan(local_path)

            text, extract_meta = scanning.extract_pdf_text(local_path)

            db.add(
                ScanReport(
                    file_id=db_file.id,
                    scanner=clam_result.scanner,
                    status=clam_result.status,
                    details=clam_result.details,
                    risk_score=clam_result.risk_score,
                )
            )

            db.add(
                ScanReport(
                    file_id=db_file.id,
                    scanner=pdf_result.scanner,
                    status=pdf_result.status,
                    details=pdf_result.details,
                    risk_score=pdf_result.risk_score,
                )
            )

            db.commit()

            if extract_meta.get("encrypted"):
                db_file.status = FileStatus.rejected
                db_file.scan_status = ScanStatus.suspicious
                db_file.risk_score = 100
                db.commit()
                return

            if clam_result.status == "infected":
                db_file.status = FileStatus.rejected
                db_file.scan_status = ScanStatus.infected
                db_file.risk_score = 100
                db.commit()
                return

            if clam_result.status == "error" and settings.enable_clamav:
                db_file.status = FileStatus.manual_review
                db_file.scan_status = ScanStatus.error
                db_file.risk_score = max(
                    clam_result.risk_score,
                    pdf_result.risk_score,
                )
                db.commit()
                return

            risk_score = max(
                clam_result.risk_score,
                pdf_result.risk_score,
            )

            db_file.risk_score = risk_score

            category_name, confidence = classification.classify_text(
                text=text,
                suggested_category=db_file.suggested_category,
            )

            category = None

            if category_name:
                category = db.scalar(
                    select(Category).where(Category.name == category_name)
                )

            if category is None:
                category = db.scalar(
                    select(Category).where(Category.name == "Other")
                )

            if category:
                db_file.category_id = category.id

            db_file.text_excerpt = (text or "")[:5000]

            if risk_score >= settings.high_risk_threshold:
                db_file.status = FileStatus.manual_review
                db_file.scan_status = ScanStatus.suspicious
                db.commit()
                return

            safe_name = sanitize_filename(db_file.original_filename)
            approved_key = f"approved/{db_file.id}/{safe_name}"

            storage.move_object(
                source_bucket=settings.quarantine_bucket,
                source_key=db_file.quarantine_key,
                destination_bucket=settings.approved_bucket,
                destination_key=approved_key,
            )

            db_file.approved_key = approved_key
            db_file.status = FileStatus.published
            db_file.scan_status = ScanStatus.clean
            db_file.published_at = datetime.utcnow()

            db.commit()

    except Exception as exc:
        db.rollback()

        try:
            db_file = db.get(FileModel, file_id)

            if db_file:
                db_file.status = FileStatus.manual_review
                db_file.scan_status = ScanStatus.error
                db.commit()
        except Exception:
            pass

        print(f"Scan failed for file {file_id}: {exc}")

    finally:
        db.close()