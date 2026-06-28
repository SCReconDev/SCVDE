import time
from pathlib import Path

import tensorflow as tf
from tensorflow.keras.preprocessing.sequence import pad_sequences

from app.detectors.base import BaseDetector, DetectorPrediction


class KerasAdapter(BaseDetector):
    detector_type = "ml_model"

    def __init__(self, model_id: str, model_dir: Path, config: dict):
        self.detector_id = model_id
        self.model_dir = model_dir
        self.config = config
        self.model = None
        self.tokenizer = None

    def load(self) -> None:
        paths = self.config.get("paths", {})

        model_path = self.model_dir / paths["model"]
        tokenizer_path = self.model_dir / paths["tokenizer"]

        if not model_path.exists():
            raise FileNotFoundError(f"Keras model not found: {model_path}")

        if not tokenizer_path.exists():
            raise FileNotFoundError(f"Keras tokenizer not found: {tokenizer_path}")

        self.model = tf.keras.models.load_model(str(model_path))

        tokenizer_json = tokenizer_path.read_text(encoding="utf-8")
        self.tokenizer = tf.keras.preprocessing.text.tokenizer_from_json(tokenizer_json)

    def predict(self, snippet_id: str, code: str, file_path: str) -> DetectorPrediction:
        if self.model is None or self.tokenizer is None:
            raise RuntimeError("Keras model is not loaded")

        start = time.perf_counter()

        input_cfg = self.config.get("input", {})
        output_cfg = self.config.get("output", {})

        max_length = int(input_cfg.get("max_length", 512))
        padding = input_cfg.get("padding", "post")
        truncating = input_cfg.get("truncating", "post")
        threshold = float(output_cfg.get("threshold", 0.5))

        sequence = self.tokenizer.texts_to_sequences([code])
        padded = pad_sequences(
            sequence,
            maxlen=max_length,
            padding=padding,
            truncating=truncating,
        )

        output = self.model.predict(padded, verbose=0)

        score = float(output[0][0])
        predicted_vulnerable = score >= threshold

        runtime_ms = int((time.perf_counter() - start) * 1000)

        return DetectorPrediction(
            snippet_id=snippet_id,
            detector_id=self.detector_id,
            detector_type=self.detector_type,
            predicted_vulnerable=predicted_vulnerable,
            predicted_vulnerability_type=self.config.get("vulnerability_type"),
            confidence=score,
            predicted_lines=[],
            runtime_ms=runtime_ms,
            raw_output={
                "score": score,
                "threshold": threshold,
            },
        )