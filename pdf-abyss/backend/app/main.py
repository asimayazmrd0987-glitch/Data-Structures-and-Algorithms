from contextlib import asynccontextmanager

from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

from app.api.routes import auth, categories, files, admin
from app.core.config import settings
from app.db.base import Base
from app.db.session import engine
from app.db.seed import seed_categories, seed_admin
from app.services.storage import init_storage


@asynccontextmanager
async def lifespan(app: FastAPI):
    Base.metadata.create_all(bind=engine)
    init_storage()
    seed_categories()
    seed_admin()
    yield


app = FastAPI(
    title=settings.app_name,
    lifespan=lifespan,
)

app.add_middleware(
    CORSMiddleware,
    allow_origins=[
        o.strip().rstrip("/")
        for o in settings.frontend_url.split(",")
        if o.strip()
    ] + ["http://localhost:3000"],
    # Allows Cloudflare Pages production + preview URLs (e.g. https://pdf-abyss.pages.dev)
    allow_origin_regex=r"https://([a-z0-9-]+\.)?pages\.dev",
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

app.include_router(auth.router)
app.include_router(categories.router)
app.include_router(files.router)
app.include_router(admin.router)


@app.get("/health")
def health():
    return {
        "status": "ok",
        "app": settings.app_name,
    }