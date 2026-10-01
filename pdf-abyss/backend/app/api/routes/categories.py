from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy import select
from sqlalchemy.orm import Session

from app.core.security import get_current_admin_user
from app.core.utils import slugify
from app.db.session import get_db
from app.models import Category, User
from app.schemas import CategoryCreate, CategoryOut


router = APIRouter(tags=["categories"])


@router.get("/categories", response_model=list[CategoryOut])
def list_categories(db: Session = Depends(get_db)):
    categories = db.scalars(
        select(Category).order_by(Category.name)
    ).all()

    return categories


@router.post("/categories", response_model=CategoryOut)
def create_category(
    payload: CategoryCreate,
    db: Session = Depends(get_db),
    admin_user: User = Depends(get_current_admin_user),
):
    slug = slugify(payload.name)

    existing = db.scalar(
        select(Category).where(Category.slug == slug)
    )

    if existing:
        raise HTTPException(
            status_code=400,
            detail="Category already exists",
        )

    category = Category(
        name=payload.name,
        slug=slug,
        description=payload.description,
    )

    db.add(category)
    db.commit()
    db.refresh(category)

    return category