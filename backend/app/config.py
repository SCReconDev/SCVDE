from pathlib import Path
from pydantic import BaseModel


class Settings(BaseModel):
    

    project_root: Path = Path(__file__).resolve().parents[2]
    data_dir: Path = project_root / "data"

    datasets_dir: Path = data_dir / "datasets"
    models_dir: Path = data_dir / "models"
    runs_dir: Path = data_dir / "runs"
    exports_dir: Path = data_dir / "exports"


settings = Settings()