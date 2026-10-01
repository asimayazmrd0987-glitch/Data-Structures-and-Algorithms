import os

from sqlalchemy import select

from app.core.security import hash_password
from app.core.utils import slugify
from app.db.session import SessionLocal
from app.models import Category, User


DEFAULT_CATEGORIES = [
    ("Computer Science", "Computer science courses, papers, books, and notes"),
    ("Software Engineering", "Software engineering materials"),
    ("Computer Engineering", "Computer engineering materials"),
    ("Mathematics", "Mathematics books, notes, and past papers"),
    ("Physics", "Physics books, notes, and past papers"),
    ("Chemistry", "Chemistry books, notes, and past papers"),
    ("Philosophy", "Philosophy books, notes, and papers"),
    ("Psychology", "Psychology books, notes, and papers"),
    ("Other", "Other documents"),
]


def seed_categories() -> None:
    db = SessionLocal()

    try:
        for name, description in DEFAULT_CATEGORIES:
            slug = slugify(name)

            existing = db.scalar(
                select(Category).where(Category.slug == slug)
            )

            if existing:
                continue

            category = Category(
                name=name,
                slug=slug,
                description=description,
            )

            db.add(category)

        db.commit()

    finally:
        db.close()


def seed_admin() -> None:
    email = os.getenv("SEED_ADMIN_EMAIL", "admin@example.com")
    password = os.getenv("SEED_ADMIN_PASSWORD", "ChangeMe123!")

    db = SessionLocal()

    try:
        existing = db.scalar(
            select(User).where(User.email == email)
        )

        if existing:
            return

        admin = User(
            email=email,
            hashed_password=hash_password(password),
            full_name="Admin",
            is_admin=True,
            is_active=True,
        )

        db.add(admin)
        db.commit()

    finally:
        db.close()