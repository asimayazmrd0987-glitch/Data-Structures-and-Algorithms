import time
from dataclasses import dataclass

import clamd
from pypdf import PdfReader

from app.core.config import settings


@dataclass
class ScanResult:
    scanner: str
    status: str
    risk_score: int
    details: dict


def clamav_scan(file_path: str) -> ScanResult:
    if not settings.enable_clamav:
        return ScanResult(
            scanner="ClamAV",
            status="skipped",
            risk_score=0,
            details={
                "message": "ClamAV disabled in settings",
            },
        )

    try:
        client = clamd.ClamdNetworkSocket(
            host=settings.clamav_host,
            port=settings.clamav_port,
            timeout=30,
        )

        for _ in range(5):
            try:
                if client.ping():
                    break
            except Exception:
                time.sleep(2)

        with open(file_path, "rb") as f:
            result = client.instream(f)

        stream_result = result.get("stream", [])

        if stream_result and stream_result[0] == "OK":
            return ScanResult(
                scanner="ClamAV",
                status="clean",
                risk_score=0,
                details=result,
            )

        return ScanResult(
            scanner="ClamAV",
            status="infected",
            risk_score=100,
            details=result,
        )

    except Exception as exc:
        return ScanResult(
            scanner="ClamAV",
            status="error",
            risk_score=80,
            details={
                "error": str(exc),
            },
        )


HIGH_RISK_PATTERNS = [
    b"/JavaScript",
    b"/JS",
    b"/Launch",
    b"/EmbeddedFile",
    b"/RichMedia",
    b"/Attachment",
]

MEDIUM_RISK_PATTERNS = [
    b"/OpenAction",
    b"/AA",
    b"/AcroForm",
    b"/ObjStm",
    b"/URI",
    b"/SubmitForm",
    b"/ImportData",
]


def pdf_structure_scan(file_path: str) -> ScanResult:
    matches = []
    risk_score = 0

    try:
        with open(file_path, "rb") as f:
            content = f.read()

        for pattern in HIGH_RISK_PATTERNS:
            if pattern in content:
                matches.append(pattern.decode(errors="ignore"))
                risk_score += 35

        for pattern in MEDIUM_RISK_PATTERNS:
            if pattern in content:
                matches.append(pattern.decode(errors="ignore"))
                risk_score += 12

        risk_score = min(risk_score, 100)

        if risk_score >= settings.high_risk_threshold:
            status = "suspicious"
        elif risk_score >= settings.medium_risk_threshold:
            status = "suspicious"
        else:
            status = "clean"

        return ScanResult(
            scanner="PDFStructure",
            status=status,
            risk_score=risk_score,
            details={
                "matches": matches,
            },
        )

    except Exception as exc:
        return ScanResult(
            scanner="PDFStructure",
            status="error",
            risk_score=70,
            details={
                "error": str(exc),
            },
        )


def extract_pdf_text(file_path: str) -> tuple[str, dict]:
    try:
        reader = PdfReader(file_path)

        if reader.is_encrypted:
            return "", {
                "encrypted": True,
                "pages": len(reader.pages),
            }

        parts = []
        total_chars = 0

        max_pages = min(
            len(reader.pages),
            settings.max_extract_pages,
        )

        for page_number in range(max_pages):
            page = reader.pages[page_number]
            page_text = page.extract_text() or ""

            parts.append(page_text)
            total_chars += len(page_text)

            if total_chars >= settings.max_extract_chars:
                break

        text = " ".join(parts)
        text = text[: settings.max_extract_chars]

        return text, {
            "encrypted": False,
            "pages": len(reader.pages),
            "extracted_pages": max_pages,
        }

    except Exception as exc:
        return "", {
            "encrypted": False,
            "error": str(exc),
        }