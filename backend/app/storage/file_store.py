from pathlib import Path
from typing import Any

from app.config import settings
from app.storage.paths import (
    ensure_storage_dirs,
    validate_safe_id,
    utc_timestamp,
    timestamp_for_id,
    dataset_dir,
    dataset_json_path,
    snippets_dir,
    snippet_file_path,
    model_dir,
    model_config_path,
    run_dir,
    run_json_path,
    predictions_json_path,
    metrics_json_path,
    errors_json_path,
    summary_json_path,
    logs_path,
)
from app.utils.json_io import read_json, write_json, read_text, write_text


class FileStore:
   

    def __init__(self) -> None:
        ensure_storage_dirs()

    
    def storage_info(self) -> dict[str, str]:
        return {
            "data_dir": str(settings.data_dir),
            "datasets_dir": str(settings.datasets_dir),
            "models_dir": str(settings.models_dir),
            "runs_dir": str(settings.runs_dir),
            "exports_dir": str(settings.exports_dir),
        }

    
    def list_dataset_ids(self) -> list[str]:
        ensure_storage_dirs()

        dataset_ids: list[str] = []

        for child in settings.datasets_dir.iterdir():
            if child.is_dir() and (child / "dataset.json").exists():
                dataset_ids.append(child.name)

        return sorted(dataset_ids)

    def list_datasets(self) -> list[dict[str, Any]]:
     
        datasets: list[dict[str, Any]] = []

        for dataset_id in self.list_dataset_ids():
            try:
                dataset = self.get_dataset(dataset_id)
                snippets = dataset.get("snippets", [])

                datasets.append(
                    {
                        "id": dataset.get("id", dataset_id),
                        "name": dataset.get("name", dataset_id),
                        "language": dataset.get("language"),
                        "vulnerability_types": dataset.get("vulnerability_types", []),
                        "num_snippets": len(snippets),
                        "created_at": dataset.get("created_at"),
                    }
                )
            except Exception as exc:
                datasets.append(
                    {
                        "id": dataset_id,
                        "error": str(exc),
                    }
                )

        return datasets

    def get_dataset(self, dataset_id: str) -> dict[str, Any]:
        validate_safe_id(dataset_id, "dataset_id")
        return read_json(dataset_json_path(dataset_id))

    def dataset_exists(self, dataset_id: str) -> bool:
        validate_safe_id(dataset_id, "dataset_id")
        return dataset_json_path(dataset_id).exists()

    def create_dataset(
        self,
        dataset_id: str,
        name: str,
        language: str,
        vulnerability_types: list[str],
        snippets: list[dict[str, Any]] | None = None,
        overwrite: bool = False,
    ) -> dict[str, Any]:
       

       
        validate_safe_id(dataset_id, "dataset_id")

        path = dataset_dir(dataset_id)
        if path.exists() and not overwrite:
            raise FileExistsError(f"Dataset already exists: {dataset_id}")

        snippets = snippets or []

        path.mkdir(parents=True, exist_ok=True)
        snippets_dir(dataset_id).mkdir(parents=True, exist_ok=True)

        dataset = {
            "id": dataset_id,
            "name": name,
            "language": language,
            "created_at": utc_timestamp(),
            "vulnerability_types": vulnerability_types,
            "snippets": snippets,
        }

        write_json(dataset_json_path(dataset_id), dataset)
        return dataset

    def save_dataset(self, dataset_id: str, dataset: dict[str, Any]) -> None:
        validate_safe_id(dataset_id, "dataset_id")

        dataset_dir(dataset_id).mkdir(parents=True, exist_ok=True)
        snippets_dir(dataset_id).mkdir(parents=True, exist_ok=True)

        write_json(dataset_json_path(dataset_id), dataset)

    def save_snippet_code(
        self,
        dataset_id: str,
        filename: str,
        code: str,
    ) -> str:
      
        validate_safe_id(dataset_id, "dataset_id")

        if "/" in filename or "\\" in filename:
            raise ValueError("filename must not contain path separators")

        relative_path = f"snippets/{filename}"
        path = snippet_file_path(dataset_id, relative_path)
        write_text(path, code)

        return relative_path

    def read_snippet_code(self, dataset_id: str, relative_path: str) -> str:
        path = snippet_file_path(dataset_id, relative_path)
        return read_text(path)

    

    def list_model_ids(self) -> list[str]:
        ensure_storage_dirs()

        model_ids: list[str] = []

        for child in settings.models_dir.iterdir():
            if child.is_dir() and (child / "model.yaml").exists():
                model_ids.append(child.name)

        return sorted(model_ids)

    def list_models(self) -> list[dict[str, Any]]:
      
        models: list[dict[str, Any]] = []

        for model_id in self.list_model_ids():
            path = model_config_path(model_id)
            models.append(
                {
                    "id": model_id,
                    "config_path": str(path),
                    "model_dir": str(model_dir(model_id)),
                }
            )

        return models

    def model_exists(self, model_id: str) -> bool:
        validate_safe_id(model_id, "model_id")
        return model_config_path(model_id).exists()



    def list_run_ids(self) -> list[str]:
        ensure_storage_dirs()

        run_ids: list[str] = []

        for child in settings.runs_dir.iterdir():
            if child.is_dir() and (child / "run.json").exists():
                run_ids.append(child.name)

        return sorted(run_ids, reverse=True)

    def list_runs(self) -> list[dict[str, Any]]:
        runs: list[dict[str, Any]] = []

        for run_id in self.list_run_ids():
            try:
                run = self.get_run(run_id)
                summary_path = summary_json_path(run_id)

                item = {
                    "id": run.get("id", run_id),
                    "dataset_id": run.get("dataset_id"),
                    "status": run.get("status"),
                    "created_at": run.get("created_at"),
                    "completed_at": run.get("completed_at"),
                    "detectors": run.get("detectors", []),
                }

                if summary_path.exists():
                    summary = read_json(summary_path)
                    item["summary_available"] = True
                    item["num_snippets"] = summary.get("num_snippets")
                else:
                    item["summary_available"] = False

                runs.append(item)

            except Exception as exc:
                runs.append(
                    {
                        "id": run_id,
                        "error": str(exc),
                    }
                )

        return runs

    def create_run(
        self,
        dataset_id: str,
        detectors: list[str],
        run_id: str | None = None,
        metadata: dict[str, Any] | None = None,
    ) -> dict[str, Any]:
        validate_safe_id(dataset_id, "dataset_id")

        if not self.dataset_exists(dataset_id):
            raise FileNotFoundError(f"Dataset does not exist: {dataset_id}")

        if run_id is None:
            run_id = f"run_{timestamp_for_id()}"

        validate_safe_id(run_id, "run_id")

        path = run_dir(run_id)
        if path.exists():
            raise FileExistsError(f"Run already exists: {run_id}")

        path.mkdir(parents=True, exist_ok=False)

        run = {
            "id": run_id,
            "dataset_id": dataset_id,
            "detectors": detectors,
            "status": "created",
            "created_at": utc_timestamp(),
            "completed_at": None,
            "metadata": metadata or {},
        }

        write_json(run_json_path(run_id), run)
        write_json(predictions_json_path(run_id), [])
        write_json(metrics_json_path(run_id), {})
        write_json(errors_json_path(run_id), {})
        write_json(summary_json_path(run_id), {})
        write_text(logs_path(run_id), "")

        return run

    def get_run(self, run_id: str) -> dict[str, Any]:
        validate_safe_id(run_id, "run_id")
        return read_json(run_json_path(run_id))

    def save_run(self, run_id: str, run: dict[str, Any]) -> None:
        validate_safe_id(run_id, "run_id")
        write_json(run_json_path(run_id), run)

    def update_run_status(
        self,
        run_id: str,
        status: str,
        completed: bool = False,
    ) -> dict[str, Any]:
        run = self.get_run(run_id)
        run["status"] = status

        if completed:
            run["completed_at"] = utc_timestamp()

        self.save_run(run_id, run)
        return run

    def save_predictions(self, run_id: str, predictions: list[dict[str, Any]]) -> None:
        validate_safe_id(run_id, "run_id")
        write_json(predictions_json_path(run_id), predictions)

    def get_predictions(self, run_id: str) -> list[dict[str, Any]]:
        validate_safe_id(run_id, "run_id")
        return read_json(predictions_json_path(run_id))

    def save_metrics(self, run_id: str, metrics: dict[str, Any]) -> None:
        validate_safe_id(run_id, "run_id")
        write_json(metrics_json_path(run_id), metrics)

    def get_metrics(self, run_id: str) -> dict[str, Any]:
        validate_safe_id(run_id, "run_id")
        return read_json(metrics_json_path(run_id))

    def save_errors(self, run_id: str, errors: dict[str, Any]) -> None:
        validate_safe_id(run_id, "run_id")
        write_json(errors_json_path(run_id), errors)

    def get_errors(self, run_id: str) -> dict[str, Any]:
        validate_safe_id(run_id, "run_id")
        return read_json(errors_json_path(run_id))

    def save_summary(self, run_id: str, summary: dict[str, Any]) -> None:
        validate_safe_id(run_id, "run_id")
        write_json(summary_json_path(run_id), summary)

    def get_summary(self, run_id: str) -> dict[str, Any]:
        validate_safe_id(run_id, "run_id")
        return read_json(summary_json_path(run_id))

    def append_log(self, run_id: str, message: str) -> None:
        validate_safe_id(run_id, "run_id")

        path = logs_path(run_id)
        path.parent.mkdir(parents=True, exist_ok=True)

        with path.open("a", encoding="utf-8") as f:
            f.write(f"[{utc_timestamp()}] {message}\n")

    def get_logs(self, run_id: str) -> str:
        validate_safe_id(run_id, "run_id")
        path = logs_path(run_id)

        if not path.exists():
            return ""

        return path.read_text(encoding="utf-8")