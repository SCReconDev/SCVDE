import json
from typing import Optional
from pathlib import Path
import typer

from app.storage.file_store import FileStore
from app.detectors.factory import list_available_detectors, create_detector
from app.evaluation.runner import EvaluationRunner
from app.generation.mistral_generator import MistralDatasetGenerator

app = typer.Typer(help="Vulnerability Evaluation Tool CLI")

datasets_app = typer.Typer(help="Dataset storage commands")
models_app = typer.Typer(help="Model storage commands")
runs_app = typer.Typer(help="Run storage commands")
storage_app = typer.Typer(help="Storage debug commands")
detectors_app = typer.Typer(help="Detector commands")

app.add_typer(detectors_app, name="detectors")
app.add_typer(storage_app, name="storage")
app.add_typer(datasets_app, name="datasets")
app.add_typer(models_app, name="models")
app.add_typer(runs_app, name="runs")


def print_json(data):
    typer.echo(json.dumps(data, indent=2, ensure_ascii=False))


@storage_app.command("info")
def storage_info():
    store = FileStore()
    print_json(store.storage_info())


@datasets_app.command("list")
def list_datasets():
    store = FileStore()
    print_json(store.list_datasets())


@datasets_app.command("create")
def create_dataset(
    dataset_id: str = typer.Option(..., "--id"),
    name: str = typer.Option(..., "--name"),
    language: str = typer.Option("python", "--language"),
    vulnerability_type: str = typer.Option("sql_injection", "--vulnerability"),
    overwrite: bool = typer.Option(False, "--overwrite"),
):
    store = FileStore()

    dataset = store.create_dataset(
        dataset_id=dataset_id,
        name=name,
        language=language,
        vulnerability_types=[vulnerability_type],
        overwrite=overwrite,
    )

    print_json(dataset)


@datasets_app.command("show")
def show_dataset(dataset_id: str):
    store = FileStore()
    print_json(store.get_dataset(dataset_id))


@datasets_app.command("add-snippet")
def add_snippet(
    dataset_id: str,
    snippet_id: str = typer.Option(..., "--snippet-id"),
    filename: str = typer.Option(..., "--filename"),
    code: str = typer.Option(..., "--code"),
    vulnerable: bool = typer.Option(..., "--vulnerable/--safe"),
    vulnerability_type: str = typer.Option("sql_injection", "--vulnerability"),
    cwe: str = typer.Option("CWE-89", "--cwe"),
    difficulty: str = typer.Option("easy", "--difficulty"),
):
    store = FileStore()

    dataset = store.get_dataset(dataset_id)

    relative_path = store.save_snippet_code(
        dataset_id=dataset_id,
        filename=filename,
        code=code,
    )

    snippet = {
        "id": snippet_id,
        "file_path": relative_path,
        "language": dataset.get("language", "python"),
        "vulnerability_type": vulnerability_type,
        "cwe": cwe,
        "is_vulnerable": vulnerable,
        "expected_vulnerable_lines": [],
        "difficulty": difficulty,
    }

    dataset.setdefault("snippets", []).append(snippet)
    store.save_dataset(dataset_id, dataset)

    print_json(snippet)


@datasets_app.command("read-snippet")
def read_snippet(dataset_id: str, snippet_id: str):
    store = FileStore()

    dataset = store.get_dataset(dataset_id)

    for snippet in dataset.get("snippets", []):
        if snippet.get("id") == snippet_id:
            code = store.read_snippet_code(dataset_id, snippet["file_path"])
            typer.echo(code)
            return

    raise typer.BadParameter(f"Snippet not found: {snippet_id}")


@datasets_app.command("generate-mistral")
def generate_mistral_dataset(
    dataset_id: str = typer.Option(..., "--id"),
    name: str = typer.Option(..., "--name"),
    vulnerability_type: str = typer.Option("sql_injection", "--vulnerability"),
    language: str = typer.Option("python", "--language"),
    num_vulnerable: int = typer.Option(10, "--num-vulnerable"),
    num_safe: int = typer.Option(10, "--num-safe"),
    batch_size: int = typer.Option(5, "--batch-size"),
    model: str = typer.Option("codestral-2508", "--model"),
    overwrite: bool = typer.Option(False, "--overwrite"),
):
    generator = MistralDatasetGenerator(model=model)

    dataset = generator.generate_dataset(
        dataset_id=dataset_id,
        name=name,
        vulnerability_type=vulnerability_type,
        language=language,
        num_vulnerable=num_vulnerable,
        num_safe=num_safe,
        batch_size=batch_size,
        overwrite=overwrite,
    )

    print_json(
        {
            "id": dataset["id"],
            "name": dataset["name"],
            "language": dataset["language"],
            "vulnerability_types": dataset["vulnerability_types"],
            "num_snippets": len(dataset["snippets"]),
            "num_vulnerable": num_vulnerable,
            "num_safe": num_safe,
        }
    )

@models_app.command("list")
def list_models():
    store = FileStore()
    print_json(store.list_models())


@runs_app.command("list")
def list_runs():
    store = FileStore()
    print_json(store.list_runs())


@runs_app.command("create")
def create_run(
    dataset_id: str = typer.Option(..., "--dataset"),
    detector: list[str] = typer.Option(..., "--detector"),
    run_id: Optional[str] = typer.Option(None, "--id"),
):
    store = FileStore()

    run = store.create_run(
        dataset_id=dataset_id,
        detectors=detector,
        run_id=run_id,
    )

    print_json(run)


@runs_app.command("show")
def show_run(run_id: str):
    store = FileStore()
    print_json(store.get_run(run_id))


@runs_app.command("summary")
def show_summary(run_id: str):
    store = FileStore()
    print_json(store.get_summary(run_id))


@runs_app.command("logs")
def show_logs(run_id: str):
    store = FileStore()
    typer.echo(store.get_logs(run_id))



@runs_app.command("execute")
def execute_run(
    dataset_id: str = typer.Option(..., "--dataset"),
    detector: list[str] = typer.Option(..., "--detector"),
    run_id: Optional[str] = typer.Option(None, "--id"),
):
    runner = EvaluationRunner()

    result = runner.run(
        dataset_id=dataset_id,
        detector_ids=detector,
        run_id=run_id,
    )

    print_json(result["summary"])



@detectors_app.command("list")
def list_detectors():
    print_json(list_available_detectors())


@detectors_app.command("test")
def test_detector(
    detector_id: str,
    dataset_id: str = typer.Option("demo_sqlinj", "--dataset"),
    snippet_id: str = typer.Option("snippet_001", "--snippet"),
):
    store = FileStore()

    dataset = store.get_dataset(dataset_id)

    snippet = next(
        item for item in dataset["snippets"] if item["id"] == snippet_id
    )

    code = store.read_snippet_code(dataset_id, snippet["file_path"])

    dataset_root = Path(store.storage_info()["datasets_dir"]) / dataset_id
    absolute_file_path = dataset_root / snippet["file_path"]

    detector = create_detector(detector_id)

    prediction = detector.predict(
        snippet_id=snippet_id,
        code=code,
        file_path=str(absolute_file_path),
    )

    print_json(prediction.__dict__)


if __name__ == "__main__":
    app()