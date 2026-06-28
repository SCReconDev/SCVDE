from fastapi import APIRouter

from app.detectors.factory import list_available_detectors
from app.storage.file_store import FileStore


router = APIRouter()
store = FileStore()


@router.get("")
def list_detectors():
    return list_available_detectors()


@router.get("/models")
def list_models():
    return store.list_models()