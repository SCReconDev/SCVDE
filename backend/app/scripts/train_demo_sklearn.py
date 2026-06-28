from pathlib import Path

import joblib
import yaml
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.linear_model import LogisticRegression
from sklearn.pipeline import Pipeline

from app.config import settings


def main():
    model_id = "sklearn_demo_sqlinj"
    model_dir = settings.models_dir / model_id
    model_dir.mkdir(parents=True, exist_ok=True)

    texts = [
        '"SELECT * FROM users WHERE id = " + user_id',
        'f"SELECT * FROM users WHERE name = {name}"',
        '"SELECT * FROM users WHERE id = ?" cursor.execute(query, (user_id,))',
        '"SELECT * FROM users WHERE name = ?" cursor.execute(query, (name,))',
    ]

    labels = [1, 1, 0, 0]

    pipeline = Pipeline(
        [
            ("tfidf", TfidfVectorizer()),
            ("clf", LogisticRegression()),
        ]
    )

    pipeline.fit(texts, labels)

    joblib.dump(pipeline, model_dir / "model.joblib")

    config = {
        "id": model_id,
        "name": "Demo scikit-learn SQL Injection Detector",
        "backend": "sklearn",
        "task": "binary_classification",
        "vulnerability_type": "sql_injection",
        "paths": {
            "model": "model.joblib",
        },
        "output": {
            "vulnerable_label": 1,
            "threshold": 0.5,
        },
    }

    with (model_dir / "model.yaml").open("w", encoding="utf-8") as f:
        yaml.safe_dump(config, f, sort_keys=False)

    print(f"Saved demo model to: {model_dir}")


if __name__ == "__main__":
    main()