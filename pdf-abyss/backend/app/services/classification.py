CATEGORY_KEYWORDS = {
    "Computer Science": [
        "computer science",
        "algorithm",
        "data structure",
        "operating system",
        "compiler",
        "machine learning",
        "database",
        "programming",
        "python",
        "java",
        "c++",
        "software",
        "computation",
    ],
    "Software Engineering": [
        "software engineering",
        "software design",
        "software architecture",
        "agile",
        "testing",
        "requirements",
        "devops",
        "maintenance",
    ],
    "Computer Engineering": [
        "computer engineering",
        "microprocessor",
        "digital logic",
        "embedded system",
        "computer architecture",
        "circuits",
        "hardware",
    ],
    "Mathematics": [
        "mathematics",
        "calculus",
        "linear algebra",
        "theorem",
        "proof",
        "probability",
        "statistics",
        "discrete mathematics",
    ],
    "Physics": [
        "physics",
        "quantum",
        "mechanics",
        "thermodynamics",
        "electromagnetism",
        "relativity",
        "particle",
    ],
    "Chemistry": [
        "chemistry",
        "organic chemistry",
        "inorganic chemistry",
        "molecule",
        "chemical reaction",
        "periodic table",
    ],
    "Philosophy": [
        "philosophy",
        "ethics",
        "metaphysics",
        "epistemology",
        "plato",
        "aristotle",
        "kant",
    ],
    "Psychology": [
        "psychology",
        "cognitive",
        "behavior",
        "personality",
        "mental",
        "neuroscience",
    ],
    "Other": [],
}


def normalize_suggested_category(value: str | None) -> str | None:
    if not value:
        return None

    cleaned = value.replace("-", " ").strip()

    for category in CATEGORY_KEYWORDS:
        if category.lower() == cleaned.lower():
            return category

    return cleaned


def classify_text(
    text: str,
    suggested_category: str | None = None,
) -> tuple[str | None, float]:
    text = (text or "").lower()

    scores = {}

    for category, keywords in CATEGORY_KEYWORDS.items():
        score = 0

        for keyword in keywords:
            count = text.count(keyword.lower())
            if count:
                score += min(count, 5)

        scores[category] = score

    best_category = max(scores, key=scores.get)

    if scores[best_category] == 0:
        suggested = normalize_suggested_category(suggested_category)

        if suggested:
            return suggested, 0.35

        return None, 0.0

    total_score = sum(scores.values()) or 1
    confidence = scores[best_category] / total_score

    suggested = normalize_suggested_category(suggested_category)

    if suggested and suggested.lower() == best_category.lower():
        confidence += 0.1

    confidence = min(confidence, 0.99)

    return best_category, round(confidence, 2)