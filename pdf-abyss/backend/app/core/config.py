from pydantic_settings import BaseSettings, SettingsConfigDict


class Settings(BaseSettings):
    model_config = SettingsConfigDict(env_file=".env", extra="ignore")

    app_name: str = "PDF Library"
    environment: str = "development"

    secret_key: str = "change-me"
    access_token_expire_minutes: int = 60 * 24

    database_url: str = "postgresql+psycopg://app:app@db:5432/pdflibrary"
    redis_url: str = "redis://redis:6379/0"

    s3_endpoint_url: str = "http://minio:9000"
    s3_access_key: str = "minioadmin"
    s3_secret_key: str = "minioadmin"

    quarantine_bucket: str = "quarantine"
    approved_bucket: str = "approved"

    max_upload_mb: int = 50

    enable_clamav: bool = False
    clamav_host: str = "clamav"
    clamav_port: int = 3310

    frontend_url: str = "http://localhost:3000"

    presigned_download_expiry_seconds: int = 3600

    max_extract_pages: int = 20
    max_extract_chars: int = 20000

    high_risk_threshold: int = 60
    medium_risk_threshold: int = 30


settings = Settings()