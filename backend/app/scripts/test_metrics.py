from app.storage.file_store import FileStore
from app.evaluation.metrics import compute_all_metrics, compute_errors, build_summary


def main():
    store = FileStore()

    dataset = store.get_dataset("demo_sqlinj")

    predictions = [
        {
            "snippet_id": "snippet_001",
            "detector_id": "dummy_always_safe",
            "detector_type": "dummy",
            "predicted_vulnerable": False,
            "runtime_ms": 1,
        },
        {
            "snippet_id": "snippet_002",
            "detector_id": "dummy_always_safe",
            "detector_type": "dummy",
            "predicted_vulnerable": False,
            "runtime_ms": 1,
        },
        {
            "snippet_id": "snippet_003",
            "detector_id": "dummy_always_safe",
            "detector_type": "dummy",
            "predicted_vulnerable": False,
            "runtime_ms": 1,
        },
        {
            "snippet_id": "snippet_004",
            "detector_id": "dummy_always_safe",
            "detector_type": "dummy",
            "predicted_vulnerable": False,
            "runtime_ms": 1,
        },
    ]

    run = store.create_run(
        dataset_id="demo_sqlinj",
        detectors=["dummy_always_safe"],
    )

    metrics = compute_all_metrics(dataset, predictions)
    errors = compute_errors(dataset, predictions)

    store.save_predictions(run["id"], predictions)
    store.save_metrics(run["id"], metrics)
    store.save_errors(run["id"], errors)

    run = store.update_run_status(run["id"], "completed", completed=True)
    summary = build_summary(run, dataset, metrics)
    store.save_summary(run["id"], summary)

    print("Metrics:")
    print(metrics)

    print("\nErrors:")
    print(errors)

    print(f"\nSaved run: {run['id']}")


if __name__ == "__main__":
    main()