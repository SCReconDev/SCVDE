from pathlib import Path
from typing import Any

import yaml

from app.config import settings
from app.detectors.base import BaseDetector



BUILTIN_DETECTORS = {
    "semgrep": {
        "id": "semgrep",
        "type": "static_analyzer",
        "name": "Semgrep",
        "backend": "semgrep",
    },
    "bandit": {
        "id": "bandit",
        "type": "static_analyzer",
        "name": "Bandit",
        "backend": "bandit",
    },
    "cppcheck": {
        "id": "cppcheck",
        "type": "static_analyzer",
        "name": "Cppcheck",
        "backend": "cppcheck",
    },

    "ruff_security": {
        "id": "ruff_security",
        "type": "static_analyzer",
        "name": "Ruff Security Rules",
        "backend": "ruff",
    },

    "codeql": {
        "id": "codeql",
        "type": "static_analyzer",
        "name": "CodeQL",
        "backend": "codeql",
    },

    "flawfinder": {
        "id": "flawfinder",
        "type": "static_analyzer",
        "name": "Flawfinder",
        "backend": "flawfinder",
    },

    "clang_static_analyzer": {
        "id": "clang_static_analyzer",
        "type": "static_analyzer",
        "name": "Clang Static Analyzer",
        "backend": "clang",
    },

    "clang_tidy_security": {
        "id": "clang_tidy_security",
        "type": "static_analyzer",
        "name": "Clang-Tidy Security",
        "backend": "clang-tidy",
    },
}


def load_model_config(model_id: str) -> dict[str, Any]:
    model_dir = settings.models_dir / model_id
    config_path = model_dir / "model.yaml"

    if not config_path.exists():
        raise FileNotFoundError(f"Model config not found: {config_path}")

    with config_path.open("r", encoding="utf-8") as file:
        config = yaml.safe_load(file)

    if not isinstance(config, dict):
        raise ValueError(f"Invalid model config: {config_path}")

    return config


def list_file_model_detectors() -> list[dict[str, Any]]:
    if not settings.models_dir.exists():
        return []

    detectors: list[dict[str, Any]] = []

    for model_dir in sorted(settings.models_dir.iterdir()):
        if not model_dir.is_dir():
            continue

        config_path = model_dir / "model.yaml"
        if not config_path.exists():
            continue

        try:
            config = load_model_config(model_dir.name)
            detectors.append(
                {
                    "id": model_dir.name,
                    "type": "ml_model",
                    "name": config.get("name", model_dir.name),
                    "backend": config.get("backend", "unknown"),
                    "vulnerability_type": config.get("vulnerability_type"),
                }
            )
        except Exception as exc:
            detectors.append(
                {
                    "id": model_dir.name,
                    "type": "ml_model",
                    "name": model_dir.name,
                    "backend": "unknown",
                    "error": str(exc),
                }
            )

    return detectors


def list_available_detectors() -> list[dict[str, Any]]:
    return list(BUILTIN_DETECTORS.values()) + list_file_model_detectors()


def create_builtin_detector(detector_id: str) -> BaseDetector:

    if detector_id == "semgrep":
        from app.static_analysis.semgrep_adapter import SemgrepAdapter

        return SemgrepAdapter()

    if detector_id == "bandit":
        from app.static_analysis.bandit_adapter import BanditAdapter

        return BanditAdapter()

    if detector_id == "cppcheck":
        from app.static_analysis.cppcheck_adapter import CppcheckAdapter

        return CppcheckAdapter()
    if detector_id == "ruff_security":
        from app.static_analysis.ruff_adapter import RuffSecurityAdapter

        return RuffSecurityAdapter()
    
    if detector_id == "codeql":
        from app.static_analysis.codeql_adapter import CodeQLAdapter

        return CodeQLAdapter()
    
    if detector_id == "flawfinder":
        from app.static_analysis.flawfinder_adapter import FlawfinderAdapter

        return FlawfinderAdapter()
    
    if detector_id == "clang_static_analyzer":
        from app.static_analysis.clang_static_analyzer_adapter import (
            ClangStaticAnalyzerAdapter,
        )

        return ClangStaticAnalyzerAdapter()
    
    if detector_id == "clang_tidy_security":
        from app.static_analysis.clang_tidy_adapter import (
            ClangTidySecurityAdapter,
        )

        return ClangTidySecurityAdapter()

    raise ValueError(f"Unknown built-in detector: {detector_id}")


def create_model_detector(detector_id: str) -> BaseDetector:
    config = load_model_config(detector_id)
    model_dir = settings.models_dir / detector_id
    backend = config.get("backend")

    if backend == "sklearn":
        from app.detectors.sklearn_adapter import SklearnAdapter

        return SklearnAdapter(
            model_id=detector_id,
            model_dir=model_dir,
            config=config,
        )

    if backend == "huggingface":
        from app.detectors.huggingface_adapter import HuggingFaceAdapter

        return HuggingFaceAdapter(
            model_id=detector_id,
            model_dir=model_dir,
            config=config,
        )

    if backend == "keras":
        from app.detectors.keras_adapter import KerasAdapter

        return KerasAdapter(
            model_id=detector_id,
            model_dir=model_dir,
            config=config,
        )

    raise ValueError(
        f"Unsupported model backend for {detector_id}: {backend!r}"
    )


def create_detector(detector_id: str) -> BaseDetector:
    if detector_id in BUILTIN_DETECTORS:
        detector = create_builtin_detector(detector_id)
    else:
        detector = create_model_detector(detector_id)

    detector.load()
    return detector