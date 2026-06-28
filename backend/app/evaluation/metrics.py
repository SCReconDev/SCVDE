from collections import defaultdict
from typing import Any


def safe_divide(numerator: float, denominator: float) -> float:
    if denominator == 0:
        return 0.0
    return numerator / denominator


def build_ground_truth_map(dataset: dict[str, Any]) -> dict[str, bool]:
    return {
        snippet["id"]: bool(snippet["is_vulnerable"])
        for snippet in dataset.get("snippets", [])
    }


def group_predictions_by_detector(
    predictions: list[dict[str, Any]],
) -> dict[str, list[dict[str, Any]]]:
    grouped = defaultdict(list)

    for prediction in predictions:
        grouped[prediction["detector_id"]].append(prediction)

    return dict(grouped)


def compute_metrics_for_detector(
    dataset: dict[str, Any],
    predictions: list[dict[str, Any]],
) -> dict[str, Any]:
    ground_truth = build_ground_truth_map(dataset)

    tp = 0
    fp = 0
    tn = 0
    fn = 0
    total_runtime_ms = 0

    evaluated_snippets = 0

    for prediction in predictions:
        snippet_id = prediction["snippet_id"]

        if snippet_id not in ground_truth:
            continue

        actual = ground_truth[snippet_id]
        predicted = bool(prediction["predicted_vulnerable"])

        total_runtime_ms += int(prediction.get("runtime_ms") or 0)
        evaluated_snippets += 1

        if actual is True and predicted is True:
            tp += 1
        elif actual is False and predicted is True:
            fp += 1
        elif actual is False and predicted is False:
            tn += 1
        elif actual is True and predicted is False:
            fn += 1

    total = tp + fp + tn + fn

    accuracy = safe_divide(tp + tn, total)
    precision = safe_divide(tp, tp + fp)
    recall = safe_divide(tp, tp + fn)
    f1 = safe_divide(2 * precision * recall, precision + recall)

    false_positive_rate = safe_divide(fp, fp + tn)
    false_negative_rate = safe_divide(fn, fn + tp)

    avg_runtime_ms = safe_divide(total_runtime_ms, evaluated_snippets)

    detector_id = predictions[0]["detector_id"] if predictions else None
    detector_type = predictions[0].get("detector_type") if predictions else None

    return {
        "detector_id": detector_id,
        "detector_type": detector_type,
        "num_evaluated": evaluated_snippets,
        "true_positives": tp,
        "false_positives": fp,
        "true_negatives": tn,
        "false_negatives": fn,
        "accuracy": round(accuracy, 4),
        "precision": round(precision, 4),
        "recall": round(recall, 4),
        "f1": round(f1, 4),
        "false_positive_rate": round(false_positive_rate, 4),
        "false_negative_rate": round(false_negative_rate, 4),
        "avg_runtime_ms": round(avg_runtime_ms, 2),
    }


def compute_all_metrics(
    dataset: dict[str, Any],
    predictions: list[dict[str, Any]],
) -> dict[str, Any]:
    grouped = group_predictions_by_detector(predictions)

    return {
        detector_id: compute_metrics_for_detector(dataset, detector_predictions)
        for detector_id, detector_predictions in grouped.items()
    }


def compute_errors(
    dataset: dict[str, Any],
    predictions: list[dict[str, Any]],
) -> dict[str, Any]:
    ground_truth = build_ground_truth_map(dataset)
    snippets_by_id = {
        snippet["id"]: snippet
        for snippet in dataset.get("snippets", [])
    }

    errors: dict[str, Any] = {}

    grouped = group_predictions_by_detector(predictions)

    for detector_id, detector_predictions in grouped.items():
        detector_errors = {
            "false_positives": [],
            "false_negatives": [],
        }

        for prediction in detector_predictions:
            snippet_id = prediction["snippet_id"]

            if snippet_id not in ground_truth:
                continue

            actual = ground_truth[snippet_id]
            predicted = bool(prediction["predicted_vulnerable"])

            if actual is False and predicted is True:
                detector_errors["false_positives"].append(
                    {
                        "snippet": snippets_by_id[snippet_id],
                        "prediction": prediction,
                    }
                )

            elif actual is True and predicted is False:
                detector_errors["false_negatives"].append(
                    {
                        "snippet": snippets_by_id[snippet_id],
                        "prediction": prediction,
                    }
                )

        errors[detector_id] = detector_errors

    return errors


def build_summary(
    run: dict[str, Any],
    dataset: dict[str, Any],
    metrics: dict[str, Any],
) -> dict[str, Any]:
    return {
        "run_id": run["id"],
        "dataset_id": run["dataset_id"],
        "status": run["status"],
        "created_at": run.get("created_at"),
        "completed_at": run.get("completed_at"),
        "num_snippets": len(dataset.get("snippets", [])),
        "detectors": list(metrics.values()),
    }