from urllib.parse import quote

import boto3
from botocore.exceptions import ClientError

from app.core.config import settings


s3_client = boto3.client(
    "s3",
    endpoint_url=settings.s3_endpoint_url,
    aws_access_key_id=settings.s3_access_key,
    aws_secret_access_key=settings.s3_secret_key,
    region_name="us-east-1",
)


def ensure_bucket(bucket_name: str) -> None:
    try:
        s3_client.head_bucket(Bucket=bucket_name)
    except ClientError:
        try:
            s3_client.create_bucket(Bucket=bucket_name)
        except ClientError:
            pass


def init_storage() -> None:
    ensure_bucket(settings.quarantine_bucket)
    ensure_bucket(settings.approved_bucket)


def upload_file(bucket_name: str, key: str, local_path: str) -> None:
    s3_client.upload_file(local_path, bucket_name, key)


def download_file(bucket_name: str, key: str, local_path: str) -> None:
    s3_client.download_file(bucket_name, key, local_path)


def move_object(
    source_bucket: str,
    source_key: str,
    destination_bucket: str,
    destination_key: str,
) -> None:
    copy_source = {
        "Bucket": source_bucket,
        "Key": source_key,
    }

    s3_client.copy_object(
        CopySource=copy_source,
        Bucket=destination_bucket,
        Key=destination_key,
    )

    s3_client.delete_object(
        Bucket=source_bucket,
        Key=source_key,
    )


def generate_presigned_download_url(
    bucket_name: str,
    key: str,
    filename: str,
) -> str:
    safe_filename = quote(filename)

    url = s3_client.generate_presigned_url(
        "get_object",
        Params={
            "Bucket": bucket_name,
            "Key": key,
            "ResponseContentDisposition": f"attachment; filename*=UTF-8''{safe_filename}",
        },
        ExpiresIn=settings.presigned_download_expiry_seconds,
    )

    return url