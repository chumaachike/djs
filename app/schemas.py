from datetime import datetime
from pydantic import BaseModel, Field

class JobCreate(BaseModel):
    job_type: str
    payload: dict

class SleepPayload(BaseModel):
    seconds: int = Field(gt=0, le=60)

class FactorialPayload(BaseModel):
    n: int = Field(ge=0, le=100)

class JobResponse(BaseModel):
    job_id: int
    job_type: str
    payload: dict
    status: str
    result: dict | None = None
    error: str | None = None
    attempts: int
    locked_by: str | None = None
    created_at: datetime
    started_at: datetime | None = None
    finished_at: datetime | None = None

    model_config = {"from_attributes": True}