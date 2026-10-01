from datetime import datetime

from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy import select
from sqlalchemy.orm import Session

from app.core.config import settings
from app.core.security import get_current_admin_user
from app.core.utils import sanitize_filename
from app.db.session import get_db
from app.models import File as FileModel, FileStatus, User
from app.schemas import FileOut
from app.services import storage


router = APIRouter(
    prefix="/admin",
    tags=["admin"],
    dependencies=[Depends(get_current_admin_user)],
)


@router.get("/files", response_model=list[FileOut])
def list_all_files(db: Session = Depends(get_db)):
    files = db.scalars(
        select(FileModel).order_by(FileModel.created_at.desc()).limit(200)
    ).all()

    return files


@router.post("/files/{file_id}/publish")
def publish_file(file_id: int, db: Session = Depends(get_db)):
    db_file = db.get(FileModel, file_id)

    if not db_file:
        raise HTTPException(
            status_code=404,
            detail="File not found",
        )

    if db_file.status == FileStatus.published:
        return {"detail": "Already published"}

    if db_file.quarantine_key and not db_file.approved_key:
        safe_name = sanitize_filename(db_file.original_filename)
        approved_key = f"approved/{db_file.id}/{safe_name}"

        try:
            storage.move_object(
                source_bucket=settings.quarantine_bucket,
                source_key=db_file.quarantine_key,
                destination_bucket=settings.approved_bucket,
                destination_key=approved_key,
            )
        except Exception:
            pass

        db_file.approved_key = approved_key

    db_file.status = FileStatus.published
    db_file.scan_status = "clean"
    db_file.published_at = datetime.utcnow()

    db.commit()

    return {"detail": "File published"}


@router.post("/files/{file_id}/reject")
def reject_file(file_id: int, db: Session = Depends(get_db)):
    db_file = db.get(FileModel, file_id)

    if not db_file:
        raise HTTPException(
            status_code=404,
            detail="File not found",
        )

    db_file.status = FileStatus.rejected
    db.commit()

    return {"detail": "File rejected"}