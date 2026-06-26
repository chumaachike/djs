from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy import select
from sqlalchemy.orm import Session

from database import get_db
from models import Job
from fastapi import Depends, Query
from schemas import JobCreate, JobResponse, SleepPayload, FactorialPayload

router = APIRouter()

def validate_payload(job_type: str, payload: dict) -> dict:
    if job_type == "sleep":
        return SleepPayload.model_validate(payload).model_dump()

    if job_type == "factorial":
        return FactorialPayload.model_validate(payload).model_dump()

    raise HTTPException(status_code=400, detail="Unknown job_type")


@router.post("/jobs", response_model=JobResponse)
def create_job(job: JobCreate, db: Session = Depends(get_db)):
    validated_payload = validate_payload(job.job_type, job.payload)

    db_job = Job(
        job_type=job.job_type,
        payload=validated_payload,
        status="queued",
    )

    db.add(db_job)
    db.commit()
    db.refresh(db_job)

    return db_job


@router.get("/jobs/{job_id}", response_model=JobResponse)
def get_job(job_id: int, db: Session = Depends(get_db)):
    job = db.get(Job, job_id)

    if job is None:
        raise HTTPException(status_code=404, detail="Job not found")

    return job

@router.get("/jobs/", response_model=list[JobResponse])
def get_jobs(db: Session = Depends(get_db), skip: int =0, limit: int = Query(default=100, le=100)):
    
    statement = select(Job).offset(skip).limit(limit)

    jobs = db.scalars(statement).all()

    return jobs