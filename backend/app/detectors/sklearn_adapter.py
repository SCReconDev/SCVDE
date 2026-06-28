import time
from pathlib import Path

import joblib

from app.detectors.base import BaseDetector, DetectorPrediction


class SklearnAdapter(BaseDetector):
    detector_type = "ml_model"

    def __init__(self, model_id: str, model_dir: Path, config: dict):
        self.detector_id = model_id
        self.model_dir = model_dir
        self.config = config
        self.model = None

    def load(self) -> None:
        model_path = self.model_dir / self.config["paths"]["model"]

        if not model_path.exists():
            raise FileNotFoundError(f"scikit-learn model not found: {model_path}")

        self.model = joblib.load(model_path)

    def predict(self, snippet_id: str, code: str, file_path: str) -> DetectorPrediction:
        if self.model is None:
            raise RuntimeError("Model is not loaded")

        start = time.perf_counter()

        output_cfg = self.config.get("output", {})
        vulnerable_label = output_cfg.get("vulnerable_label", 1)
        threshold = output_cfg.get("threshold", 0.5)

        confidence = None
        raw_output = {}

        if hasattr(self.model, "predict_proba"):
            probs = self.model.predict_proba([code])[0]
            classes = list(self.model.classes_)

            if vulnerable_label in classes:
                vulnerable_index = classes.index(vulnerable_label)
            elif str(vulnerable_label) in classes:
                vulnerable_index = classes.index(str(vulnerable_label))
            else:
                raise ValueError(
                    f"Vulnerable label {vulnerable_label} not found in model classes: {classes}"
                )

            confidence = float(probs[vulnerable_index])
            predicted_vulnerable = confidence >= threshold

            raw_output = {
                "classes": [str(c) for c in classes],
                "probabilities": [float(p) for p in probs],
            }

        else:
            pred = self.model.predict([code])[0]
            predicted_vulnerable = str(pred) == str(vulnerable_label)

            raw_output = {
                "prediction": str(pred),
            }

        runtime_ms = int((time.perf_counter() - start) * 1000)

        return DetectorPrediction(
            snippet_id=snippet_id,
            detector_id=self.detector_id,
            detector_type=self.detector_type,
            predicted_vulnerable=predicted_vulnerable,
            predicted_vulnerability_type=self.config.get("vulnerability_type"),
            confidence=confidence,
            predicted_lines=[],
            runtime_ms=runtime_ms,
            raw_output=raw_output,
        )