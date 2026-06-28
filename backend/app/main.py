from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

from app.api.datasets import router as datasets_router
from app.api.detectors import router as detectors_router
from app.api.runs import router as runs_router


app = FastAPI(
    title="SC Vulnerability Detection Evaluator API",
    version="42",
)

app.add_middleware(
    CORSMiddleware,
    allow_origins=[
        "http://localhost:5173",
        "http://localhost:3000",
    ],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


@app.get("/health")
def health():
    return {"status": "ok"}


app.include_router(datasets_router, prefix="/datasets", tags=["datasets"])
app.include_router(detectors_router, prefix="/detectors", tags=["detectors"])
app.include_router(runs_router, prefix="/runs", tags=["runs"])