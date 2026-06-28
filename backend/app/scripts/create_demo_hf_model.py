from transformers import AutoModelForSequenceClassification, AutoTokenizer

from app.config import settings


def main():
    model_id = "hf_demo_tiny"
    output_dir = settings.models_dir / model_id
    output_dir.mkdir(parents=True, exist_ok=True)

    base_model = "hf-internal-testing/tiny-random-bert"

    tokenizer = AutoTokenizer.from_pretrained(base_model)
    model = AutoModelForSequenceClassification.from_pretrained(
        base_model,
        num_labels=2,
    )

    tokenizer.save_pretrained(output_dir)
    model.save_pretrained(output_dir)

    model_yaml = """id: hf_demo_tiny
name: Demo Hugging Face Tiny Classifier
backend: huggingface
task: binary_classification
vulnerability_type: sql_injection

paths:
  model_dir: .

input:
  max_length: 128

output:
  vulnerable_label: 1
  threshold: 0.5
"""

    (output_dir / "model.yaml").write_text(model_yaml, encoding="utf-8")

    


if __name__ == "__main__":
    main()