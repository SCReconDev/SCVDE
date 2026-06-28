from datetime import datetime, timezone
from pathlib import Path
import re

from app.config import settings


SAFE_ID_PATTERN = re.compile(r"^[a-zA-Z0-9_\-]+$")


def ensure_storage_dirs() -> None:
  
    settings.data_dir.mkdir(parents=True, exist_ok=True)
    settings.datasets_dir.mkdir(parents=True, exist_ok=True)
    settings.models_dir.mkdir(parents=True, exist_ok=True)
    settings.runs_dir.mkdir(parents=True, exist_ok=True)
    settings.exports_dir.mkdir(parents=True, exist_ok=True)


def validate_safe_id(value: str, field_name: str = "id") -> str:
   
    if not value:
        raise ValueError(f"{field_name} cannot be empty")

    if not SAFE_ID_PATTERN.match(value):
        raise ValueError(
            "Only letters, numbers, underscores, and hyphens are allowed."
        )

    return value


def utc_timestamp() -> str:

    return datetime.now(timezone.utc).replace(microsecond=0).isoformat()


def timestamp_for_id() -> str:
 
    return datetime.now(timezone.utc).strftime("%Y%m%d_%H%M%S")


def dataset_dir(dataset_id: str) -> Path:
    validate_safe_id(dataset_id, "dataset_id")
    return settings.datasets_dir / dataset_id


def dataset_json_path(dataset_id: str) -> Path:
    return dataset_dir(dataset_id) / "dataset.json"


def snippets_dir(dataset_id: str) -> Path:
    return dataset_dir(dataset_id) / "snippets"


def snippet_file_path(dataset_id: str, relative_path: str) -> Path:
  
    base = dataset_dir(dataset_id).resolve()
    path = (base / relative_path).resolve()

    if not str(path).startswith(str(base)):
        raise ValueError(f"Unsafe snippet path: {relative_path}")

    return path


def model_dir(model_id: str) -> Path:
    validate_safe_id(model_id, "model_id")
    return settings.models_dir / model_id


def model_config_path(model_id: str) -> Path:

    return model_dir(model_id) / "model.yaml"


def run_dir(run_id: str) -> Path:
    validate_safe_id(run_id, "run_id")
    return settings.runs_dir / run_id


def run_json_path(run_id: str) -> Path:
    return run_dir(run_id) / "run.json"


def predictions_json_path(run_id: str) -> Path:
    return run_dir(run_id) / "predictions.json"


def metrics_json_path(run_id: str) -> Path:
    return run_dir(run_id) / "metrics.json"


def errors_json_path(run_id: str) -> Path:
    return run_dir(run_id) / "errors.json"


def summary_json_path(run_id: str) -> Path:
    return run_dir(run_id) / "summary.json"


def logs_path(run_id: str) -> Path:
    return run_dir(run_id) / "logs.txt"