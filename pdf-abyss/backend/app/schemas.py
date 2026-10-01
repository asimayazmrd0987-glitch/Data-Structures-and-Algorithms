from datetime import datetime
from typing import Optional

from pydantic import BaseModel, EmailStr, ConfigDict

from app.models import FileStatus, ScanStatus


class UserCreate(BaseModel):
    email: EmailStr
    password: str
    full_name: Optional[str] = None


class Login(BaseModel):
    email: EmailStr
    password: str


class UserOut(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    email: EmailStr
    full_name: Optional[str] = None
    is_active: bool
    is_admin: bool
    created_at: datetime


class Token(BaseModel):
    access_token: str
    token_type: str = "bearer"


class CategoryCreate(BaseModel):
    name: str
    description: Optional[str] = None


class CategoryOut(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    name: str
    slug: str
    description: Optional[str] = None


class FileOut(BaseModel):
    model_config = ConfigDict(from_attributes=True)

    id: int
    title: str
    description: Optional[str] = None
    original_filename: str
    file_size: int
    sha256: str

    status: FileStatus
    scan_status: ScanStatus
    risk_score: int

    suggested_category: Optional[str] = None

    document_type: Optional[str] = None
    institution: Optional[str] = None
    year: Optional[int] = None
    license: Optional[str] = None

    created_at: datetime
    published_at: Optional[datetime] = None

    category: Optional[CategoryOut] = None