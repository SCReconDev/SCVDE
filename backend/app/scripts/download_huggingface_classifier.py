import argparse
from pathlib import Path

import yaml
from transformers import (
    AutoConfig,
    AutoModelForSequenceClassification,
    AutoTokenizer,
)

from app.config import settings


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Download a Hugging face model"
    )

    parser.add_argument("--id", required=True)
    parser.add_argument("--source", required=True)
    parser.add_argument("--name", required=True)
    parser.add_argument("--vulnerability-type", default="general")
    parser.add_argument("--vulnerable-label", type=int, default=1)
    parser.add_argument("--threshold", type=float, default=0.5)
    parser.add_argument("--max-length", type=int, default=512)

    args = parser.parse_args()

    model_dir: Path = settings.models_dir / args.id
    model_dir.mkdir(parents=True, exist_ok=True)

    print(f"Reading model configuration: {args.source}")
    source_config = AutoConfig.from_pretrained(args.source)

    print("id2label:", source_config.id2label)
    print("label2id:", source_config.label2id)
    print("num_labels:", source_config.num_labels)

    print(f"Downloading tokenizer: {args.source}")
    tokenizer = AutoTokenizer.from_pretrained(args.source)

    print(f"Downloading model: {args.source}")
    model = AutoModelForSequenceClassification.from_pretrained(args.source)

    print(f"Saving model to: {model_dir}")
    tokenizer.save_pretrained(model_dir)
    model.save_pretrained(model_dir)

    scvde_config = {
        "id": args.id,
        "name": args.name,
        "backend": "huggingface",
        "task": "binary_classification",
        "vulnerability_type": args.vulnerability_type,
        "source_model": args.source,
        "paths": {
            "model_dir": ".",
        },
        "input": {
            "max_length": args.max_length,
        },
        "output": {
            "vulnerable_label": args.vulnerable_label,
            "threshold": args.threshold,
        },
    }

    config_path = model_dir / "model.yaml"

    with config_path.open("w", encoding="utf-8") as file:
        yaml.safe_dump(scvde_config, file, sort_keys=False)

    print(f"Saved configuration")


if __name__ == "__main__":
    main()