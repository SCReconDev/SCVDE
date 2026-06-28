from fastapi import APIRouter, HTTPException, Query

from app.storage.file_store import FileStore


router = APIRouter()
store = FileStore()


@router.get("")
def list_runs():
    return store.list_runs()


@router.get("/{run_id}")
def get_run(run_id: str):
    try:
        return store.get_run(run_id)
    except FileNotFoundError:
        raise HTTPException(status_code=404, detail="Run not found")


@router.get("/{run_id}/summary")
def get_run_summary(run_id: str):
    try:
        return store.get_summary(run_id)
    except FileNotFoundError:
        raise HTTPException(status_code=404, detail="Run summary not found")


@router.get("/{run_id}/metrics")
def get_run_metrics(run_id: str):
    try:
        return store.get_metrics(run_id)
    except FileNotFoundError:
        raise HTTPException(status_code=404, detail="Run metrics not found")


@router.get("/{run_id}/predictions")
def get_run_predictions(
    run_id: str,
    detector_id: str | None = Query(default=None),
    snippet_id: str | None = Query(default=None),
):
    try:
        predictions = store.get_predictions(run_id)

        if detector_id is not None:
            predictions = [
                item
                for item in predictions
                if item.get("detector_id") == detector_id
            ]

        if snippet_id is not None:
            predictions = [
                item
                for item in predictions
                if item.get("snippet_id") == snippet_id
            ]

        return predictions

    except FileNotFoundError:
        raise HTTPException(status_code=404, detail="Run predictions not found")


@router.get("/{run_id}/errors")
def get_run_errors(run_id: str):
    try:
        return store.get_errors(run_id)
    except FileNotFoundError:
        raise HTTPException(status_code=404, detail="Run errors not found")


@router.get("/{run_id}/errors/{detector_id}")
def get_run_errors_for_detector(run_id: str, detector_id: str):
    try:
        errors = store.get_errors(run_id)

        if detector_id not in errors:
            raise HTTPException(status_code=404, detail="Detector errors not found")

        return errors[detector_id]

    except FileNotFoundError:
        raise HTTPException(status_code=404, detail="Run errors not found")


@router.get("/{run_id}/logs")
def get_run_logs(run_id: str):
    try:
        return {
            "run_id": run_id,
            "logs": store.get_logs(run_id),
        }
    except FileNotFoundError:
        raise HTTPException(status_code=404, detail="Run logs not found")