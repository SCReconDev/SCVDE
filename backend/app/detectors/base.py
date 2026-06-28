from dataclasses import dataclass
from typing import Any, Optional
from abc import ABC, abstractmethod


@dataclass
class DetectorPrediction:
    snippet_id: str
    detector_id: str
    detector_type: str
    predicted_vulnerable: bool
    predicted_vulnerability_type: Optional[str]
    confidence: Optional[float]
    predicted_lines: list[int]
    runtime_ms: int
    raw_output: Any


class BaseDetector(ABC):
    detector_id: str
    detector_type: str

    def load(self) -> None:
        pass

    @abstractmethod
    def predict(self, snippet_id: str, code: str, file_path: str) -> DetectorPrediction:
        pass