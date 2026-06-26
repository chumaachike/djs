from pydantic import BaseModel, Field

class JobCreate(BaseModel):
    job_type: str
    payload: dict

class SleepPayload(BaseModel):
    seconds: int = Field(gt=0, le=60)

class FactorialPayload(BaseModel):
    n: int = Field(ge=0, le=100)

class JobResponse(BaseModel):
    id: int
    job_type: str
    payload: dict
    status: str
    result: dict | None = None
    error: str | None = None

    model_config = {
        "from_attributes": True
    }
