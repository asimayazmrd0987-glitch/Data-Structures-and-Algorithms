import enum
from datetime import datetime
from typing import Optional

from sqlalchemy import (
    String,
    Text,
    Integer,
    BigInteger,
    DateTime,
    ForeignKey,
    JSON,
    Boolean,
    Enum as SQLAlchemyEnum,
)
from sqlalchemy.orm import Mapped, mapped_column, relationship

from app.db.base import Base


class FileStatus(str, enum.Enum):
    uploaded = "uploaded"
    scanning = "scanning"
    published = "published"
    rejected = "rejected"
    manual_review = "manual_review"
    removed = "removed"


class ScanStatus(str, enum.Enum):
    pending = "pending"
    scanning = "scanning"
    clean = "clean"
    infected = "infected"
    suspicious = "suspicious"
    error = "error"


class User(Base):
    __tablename__ = "users"

    id: Mapped[int] = mapped_column(primary_key=True)
    email: Mapped[str] = mapped_column(String(255), unique=True, index=True)
    hashed_password: Mapped[str]
    full_name: Mapped[Optional[str]] = mapped_column(String(255), nullable=True)

    is_active: Mapped[bool] = mapped_column(Boolean, default=True)
    is_admin: Mapped[bool] = mapped_column(Boolean, default=False)

    created_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.utcnow)


class Category(Base):
    __tablename__ = "categories"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(255), unique=True, index=True)
    slug: Mapped[str] = mapped_column(String(255), unique=True, index=True)
    description: Mapped[Optional[str]] = mapped_column(Text, nullable=True)

    created_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.utcnow)

    files = relationship("File", back_populates="category")


class File(Base):
    __tablename__ = "files"

    id: Mapped[int] = mapped_column(primary_key=True)

    user_id: Mapped[Optional[int]] = mapped_column(ForeignKey("users.id"), nullable=True)

    title: Mapped[str] = mapped_column(String(500))
    description: Mapped[Optional[str]] = mapped_column(Text, nullable=True)

    original_filename: Mapped[str] = mapped_column(String(500))
    mime_type: Mapped[str] = mapped_column(String(255), default="application/pdf")
    file_size: Mapped[int] = mapped_column(BigInteger, default=0)
    sha256: Mapped[str] = mapped_column(String(64), index=True)

    quarantine_key: Mapped[str] = mapped_column(String(1000))
    approved_key: Mapped[Optional[str]] = mapped_column(String(1000), nullable=True)

    status: Mapped[FileStatus] = mapped_column(
        SQLAlchemyEnum(
            FileStatus,
            values_callable=lambda x: [e.value for e in x],
        ),
        default=FileStatus.uploaded,
        index=True,
    )

    scan_status: Mapped[ScanStatus] = mapped_column(
        SQLAlchemyEnum(
            ScanStatus,
            values_callable=lambda x: [e.value for e in x],
        ),
        default=ScanStatus.pending,
        index=True,
    )

    risk_score: Mapped[int] = mapped_column(Integer, default=0)

    suggested_category: Mapped[Optional[str]] = mapped_column(String(255), nullable=True)

    category_id: Mapped[Optional[int]] = mapped_column(
        ForeignKey("categories.id"),
        nullable=True,
    )

    text_excerpt: Mapped[Optional[str]] = mapped_column(Text, nullable=True)

    document_type: Mapped[Optional[str]] = mapped_column(String(255), nullable=True)
    institution: Mapped[Optional[str]] = mapped_column(String(255), nullable=True)
    year: Mapped[Optional[int]] = mapped_column(Integer, nullable=True)
    license: Mapped[Optional[str]] = mapped_column(String(255), nullable=True)

    created_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.utcnow)
    updated_at: Mapped[datetime] = mapped_column(
        DateTime,
        default=datetime.utcnow,
        onupdate=datetime.utcnow,
    )
    published_at: Mapped[Optional[datetime]] = mapped_column(DateTime, nullable=True)

    category: Mapped[Optional["Category"]] = relationship(
        back_populates="files"
    )


class ScanReport(Base):
    __tablename__ = "scan_reports"

    id: Mapped[int] = mapped_column(primary_key=True)

    file_id: Mapped[int] = mapped_column(ForeignKey("files.id"), index=True)

    scanner: Mapped[str] = mapped_column(String(255))
    status: Mapped[str] = mapped_column(String(100))
    details: Mapped[Optional[dict]] = mapped_column(JSON, nullable=True)
    risk_score: Mapped[int] = mapped_column(Integer, default=0)

    created_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.utcnow)