import tempfile
import uuid
from datetime import datetime
from pathlib import Path

from fastapi import (
    APIRouter,
    Depends,
    UploadFile,
    File,
    Form,
    HTTPException,
    Query,
)
from fastapi.responses import RedirectResponse
from sqlalchemy import select, or_
from sqlalchemy.orm import Session, joinedload

from app.core.config import settings
from app.core.security import get_current_user
from app.core.utils import sanitize_filename
from app.db.session import get_db
from app.models import (
    File as FileModel,
    FileStatus,
    ScanStatus,
    Category,
    User,
)
from app.schemas import FileOut
from app.services import storage
from app.services.files import validate_and_store_upload, sha256_file
from app.worker.tasks import scan_and_publish_file


router = APIRouter(tags=["files"])


@router.post("/files", response_model=FileOut, status_code=202)
def upload_pdf(
    file: UploadFile = File(...),
    title: str = Form(...),
    description: str | None = Form(None),
    suggested_category: str | None = Form(None),
    document_type: str | None = Form(None),
    institution: str | None = Form(None),
    year: int | None = Form(None),
    license: str | None = Form(None),
    db: Session = Depends(get_db),
    current_user: User = Depends(get_current_user),
):
    with tempfile.TemporaryDirectory() as tmp_dir:
        temp_path, original_filename, size = validate_and_store_upload(
            upload_file=file,
            temp_dir=Path(tmp_dir),
        )

        file_hash = sha256_file(temp_path)

        safe_name = sanitize_filename(original_filename)
        quarantine_key = f"quarantine/{uuid.uuid4()}/{safe_name}"

        storage.upload_file(
            bucket_name=settings.quarantine_bucket,
            key=quarantine_key,
            local_path=str(temp_path),
        )

        db_file = FileModel(
            user_id=current_user.id,
            title=title,
            description=description,
            original_filename=original_filename,
            mime_type="application/pdf",
            file_size=size,
            sha256=file_hash,
            quarantine_key=quarantine_key,
            status=FileStatus.uploaded,
            scan_status=ScanStatus.pending,
            suggested_category=suggested_category,
            document_type=document_type,
            institution=institution,
            year=year,
            license=license,
        )

        db.add(db_file)
        db.commit()
        db.refresh(db_file)

        scan_and_publish_file.delay(db_file.id)

        return db_file


@router.get("/files", response_model=list[FileOut])
def list_files(
    category: str | None = Query(None),
    q: str | None = Query(None),
    limit: int = Query(50, le=100),
    db: Session = Depends(get_db),
):
    query = (
        select(FileModel)
        .options(joinedload(FileModel.category))
        .where(FileModel.status == FileStatus.published)
    )

    if category:
        query = query.join(FileModel.category).where(Category.slug == category)

    if q:
        query = query.where(
            or_(
                FileModel.title.ilike(f"%{q}%"),
                FileModel.description.ilike(f"%{q}%"),
            )
        )

    query = query.order_by(FileModel.created_at.desc()).limit(limit)

    files = db.scalars(query).unique().all()

    return files


@router.get("/files/{file_id}", response_model=FileOut)
def get_file(file_id: int, db: Session = Depends(get_db)):
    db_file = db.get(FileModel, file_id)

    if not db_file or db_file.status != FileStatus.published:
        raise HTTPException(
            status_code=404,
            detail="File not found",
        )

    return db_file


@router.get("/files/{file_id}/download")
def download_file(file_id: int, db: Session = Depends(get_db)):
    db_file = db.get(FileModel, file_id)

    if not db_file or db_file.status != FileStatus.published:
        raise HTTPException(
            status_code=404,
            detail="File not found",
        )

    if not db_file.approved_key:
        raise HTTPException(
            status_code=404,
            detail="File is not available yet",
        )

    url = storage.generate_presigned_download_url(
        bucket_name=settings.approved_bucket,
        key=db_file.approved_key,
        filename=db_file.original_filename,
    )

    return RedirectResponse(url=url, status_code=302)