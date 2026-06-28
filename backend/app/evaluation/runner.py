from dataclasses import asdict
from pathlib import Path
from typing import Any

from app.detectors.factory import create_detector
from app.evaluation.metrics import compute_all_metrics, compute_errors, build_summary
from app.storage.file_store import FileStore


class EvaluationRunner:
    def __init__(self, store: FileStore | None = None):
        self.store = store or FileStore()

    def run(
        self,
        dataset_id: str,
        detector_ids: list[str],
        run_id: str | None = None,
    ) -> dict[str, Any]:
        dataset = self.store.get_dataset(dataset_id)

        run = self.store.create_run(
            dataset_id=dataset_id,
            detectors=detector_ids,
            run_id=run_id,
        )

        self.store.update_run_status(run["id"], "running")
        self.store.append_log(run["id"], "Started evaluation run")

        predictions: list[dict[str, Any]] = []

        try:
            detectors = []

            for detector_id in detector_ids:
                self.store.append_log(run["id"], f"Loading detector: {detector_id}")
                detector = create_detector(detector_id)
                detectors.append(detector)

            for snippet in dataset.get("snippets", []):
                snippet_id = snippet["id"]
                relative_path = snippet["file_path"]

                code = self.store.read_snippet_code(dataset_id, relative_path)

                dataset_root = Path(self.store.storage_info()["datasets_dir"]) / dataset_id
                absolute_file_path = str(dataset_root / relative_path)

                self.store.append_log(run["id"], f"Evaluating snippet: {snippet_id}")

                for detector in detectors:
                    prediction = detector.predict(
                        snippet_id=snippet_id,
                        code=code,
                        file_path=absolute_file_path,
                    )

                    predictions.append(asdict(prediction))

            metrics = compute_all_metrics(dataset, predictions)
            errors = compute_errors(dataset, predictions)

            self.store.save_predictions(run["id"], predictions)
            self.store.save_metrics(run["id"], metrics)
            self.store.save_errors(run["id"], errors)

            completed_run = self.store.update_run_status(
                run["id"],
                "completed",
                completed=True,
            )

            summary = build_summary(completed_run, dataset, metrics)
            self.store.save_summary(run["id"], summary)

            self.store.append_log(run["id"], "Completed evaluation run")

            return {
                "run": completed_run,
                "metrics": metrics,
                "summary": summary,
            }

        except Exception as exc:
            failed_run = self.store.update_run_status(
                run["id"],
                "failed",
                completed=True,
            )

            self.store.append_log(run["id"], f"Evaluation failed: {exc}")

            raise RuntimeError(
                f"Evaluation run failed. Run ID: {run['id']}. Error: {exc}"
            ) from exc