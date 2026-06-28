from fastapi import APIRouter, HTTPException

from app.storage.file_store import FileStore


router = APIRouter()
store = FileStore()


@router.get("")
def list_datasets():
    return store.list_datasets()


@router.get("/{dataset_id}")
def get_dataset(dataset_id: str):
    try:
        return store.get_dataset(dataset_id)
    except FileNotFoundError:
        raise HTTPException(status_code=404, detail="Dataset not found")


@router.get("/{dataset_id}/snippets/{snippet_id}")
def get_snippet(dataset_id: str, snippet_id: str):
    try:
        dataset = store.get_dataset(dataset_id)

        snippet = next(
            (
                item
                for item in dataset.get("snippets", [])
                if item.get("id") == snippet_id
            ),
            None,
        )

        if snippet is None:
            raise HTTPException(status_code=404, detail="Snippet not found")

        code = store.read_snippet_code(dataset_id, snippet["file_path"])

        return {
            "dataset_id": dataset_id,
            "snippet": snippet,
            "code": code,
        }

    except FileNotFoundError:
        raise HTTPException(status_code=404, detail="Dataset or snippet file not found")