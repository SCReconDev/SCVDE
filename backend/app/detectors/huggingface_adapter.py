import time
from pathlib import Path

import torch
from transformers import (
    AutoModelForSequenceClassification,
    AutoTokenizer,
)

from app.detectors.base import BaseDetector, DetectorPrediction


class HuggingFaceAdapter(BaseDetector):
    detector_type = "ml_model"

    def __init__(
        self,
        model_id: str,
        model_dir: Path,
        config: dict,
    ):
        self.detector_id = model_id
        self.model_dir = model_dir
        self.config = config

        self.tokenizer = None
        self.model = None

        self.device = "cuda" if torch.cuda.is_available() else "cpu"

    def load(self) -> None:
        model_subdir = self.config.get("paths", {}).get("model_dir", ".")
        model_path = self.model_dir / model_subdir

        if not model_path.exists():
            raise FileNotFoundError(
                f"Hugging Face model directory not found: {model_path}"
            )

        tokenizer_source = self.config.get("tokenizer_source")

        if tokenizer_source:
            self.tokenizer = AutoTokenizer.from_pretrained(tokenizer_source)
        else:
            self.tokenizer = AutoTokenizer.from_pretrained(str(model_path))

        self.model = AutoModelForSequenceClassification.from_pretrained(
            str(model_path)
        )

        self.model.to(self.device)
        self.model.eval()
    def predict(
        self,
        snippet_id: str,
        code: str,
        file_path: str,
    ) -> DetectorPrediction:
        if self.model is None or self.tokenizer is None:
            raise RuntimeError("Hugging Face model is not loaded")

        start = time.perf_counter()

        input_config = self.config.get("input", {})
        output_config = self.config.get("output", {})

        max_length = int(input_config.get("max_length", 512))
        vulnerable_label = int(output_config.get("vulnerable_label", 1))
        threshold = float(output_config.get("threshold", 0.5))

        encoded = self.tokenizer(
            code,
            return_tensors="pt",
            truncation=True,
            padding=True,
            max_length=max_length,
        )

        encoded = {
            key: value.to(self.device)
            for key, value in encoded.items()
        }

        with torch.no_grad():
            outputs = self.model(**encoded)
            logits = outputs.logits
            probabilities = torch.softmax(logits, dim=-1)[0]

        if vulnerable_label < 0 or vulnerable_label >= len(probabilities):
            raise ValueError(
                f"vulnerable_label={vulnerable_label} is invalid for a model "
                f"with {len(probabilities)} output labels"
            )

        confidence = float(probabilities[vulnerable_label].item())
        predicted_vulnerable = confidence >= threshold

        runtime_ms = int((time.perf_counter() - start) * 1000)

        id2label = getattr(self.model.config, "id2label", {})
        label2id = getattr(self.model.config, "label2id", {})

        return DetectorPrediction(
            snippet_id=snippet_id,
            detector_id=self.detector_id,
            detector_type=self.detector_type,
            predicted_vulnerable=predicted_vulnerable,
            predicted_vulnerability_type=(
                self.config.get("vulnerability_type", "general")
                if predicted_vulnerable
                else None
            ),
            confidence=confidence,
            predicted_lines=[],
            runtime_ms=runtime_ms,
            raw_output={
                "device": self.device,
                "threshold": threshold,
                "vulnerable_label": vulnerable_label,
                "probabilities": [
                    float(value)
                    for value in probabilities.detach().cpu().tolist()
                ],
                "id2label": {
                    str(key): value
                    for key, value in id2label.items()
                },
                "label2id": {
                    str(key): value
                    for key, value in label2id.items()
                },
                "source_model": self.config.get("source_model"),
            },
        )