import json
import os
import tempfile
from pathlib import Path
from typing import Any


def read_json(path: Path) -> Any:
 
    path = Path(path)

    if not path.exists():
        raise FileNotFoundError(f"JSON file not found: {path}")

    try:
        with path.open("r", encoding="utf-8") as f:
            return json.load(f)
    except json.JSONDecodeError as exc:
        raise ValueError(f"Invalid JSON file: {path}") from exc


def write_json(path: Path, data: Any, indent: int = 2) -> None:
  
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)

    fd, temp_path = tempfile.mkstemp(
        prefix=f".{path.name}.",
        suffix=".tmp",
        dir=str(path.parent),
        text=True,
    )

    try:
        with os.fdopen(fd, "w", encoding="utf-8") as f:
            json.dump(data, f, indent=indent, ensure_ascii=False)
            f.write("\n")

        os.replace(temp_path, path)

    except Exception:
        try:
            os.remove(temp_path)
        except FileNotFoundError:
            pass
        raise


def write_text(path: Path, content: str) -> None:
  
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)

    fd, temp_path = tempfile.mkstemp(
        prefix=f".{path.name}.",
        suffix=".tmp",
        dir=str(path.parent),
        text=True,
    )

    try:
        with os.fdopen(fd, "w", encoding="utf-8") as f:
            f.write(content)

        os.replace(temp_path, path)

    except Exception:
        try:
            os.remove(temp_path)
        except FileNotFoundError:
            pass
        raise


def read_text(path: Path) -> str:
    """
    Read a plain text file.
    """
    path = Path(path)

    if not path.exists():
        raise FileNotFoundError(f"Text file not found: {path}")

    return path.read_text(encoding="utf-8")