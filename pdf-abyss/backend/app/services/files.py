import hashlib
import uuid
from pathlib import Path

import filetype

from fastapi import UploadFile, HTTPException

from app.core.config import settings


def sha256_file(file_path: Path) -> str:
    sha256 = hashlib.sha256()

    with open(file_path, "rb") as f:
        for chunk in iter(lambda: f.read(8192), b""):
            sha256.update(chunk)

    return sha256.hexdigest()


def validate_and_store_upload(
    upload_file: UploadFile,
    temp_dir: Path,
) -> tuple[Path, str, int]:
    filename = upload_file.filename or "upload.pdf"

    if not filename.lower().endswith(".pdf"):
        raise HTTPException(
            status_code=400,
            detail="Only .pdf files are allowed",
        )

    temp_path = temp_dir / f"{uuid.uuid4()}.pdf"

    size = 0
    max_bytes = settings.max_upload_mb * 1024 * 1024

    with open(temp_path, "wb") as output_file:
        while True:
            chunk = upload_file.file.read(1024 * 1024)

            if not chunk:
                break

            size += len(chunk)

            if size > max_bytes:
                temp_path.unlink(missing_ok=True)
                raise HTTPException(
                    status_code=413,
                    detail=f"File is too large. Maximum size is {settings.max_upload_mb} MB",
                )

            output_file.write(chunk)

    if size == 0:
        temp_path.unlink(missing_ok=True)
        raise HTTPException(
            status_code=400,
            detail="Empty file",
        )

    file_kind = filetype.guess(str(temp_path))

    if file_kind is None or file_kind.mime != "application/pdf":
        temp_path.unlink(missing_ok=True)
        raise HTTPException(
            status_code=400,
            detail="File is not a valid PDF",
        )

    return temp_path, filename, size