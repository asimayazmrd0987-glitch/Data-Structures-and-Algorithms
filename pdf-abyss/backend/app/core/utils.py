import re


def slugify(text: str) -> str:
    text = text.lower().strip()
    text = re.sub(r"[^a-z0-9]+", "-", text)
    return text.strip("-")


def sanitize_filename(filename: str) -> str:
    filename = filename.replace("/", "-").replace("\\", "-")
    filename = re.sub(r"[^A-Za-z0-9._ -]+", "", filename)
    filename = filename.strip().replace(" ", "-")
    return filename[:200] or "file.pdf"