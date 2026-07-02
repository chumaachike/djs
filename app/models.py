from sqlalchemy import BigInteger, Text, DateTime, SmallInteger, func
from sqlalchemy.dialects.postgresql import JSONB, ENUM
from sqlalchemy.orm import Mapped, mapped_column

from database import Base

class Job(Base):
    __tablename__ = "jobs"

    job_id: Mapped[int] = mapped_column(BigInteger, primary_key=True, index=True)
    job_type: Mapped[str] = mapped_column(Text, nullable=False)
    payload: Mapped[dict] = mapped_column(JSONB, nullable=False)
    status: Mapped[str] = mapped_column(ENUM(
                                        "queued",
                                        "running",
                                        "succeeded",
                                        "failed",
                                        "cancelled",
                                        name="status",
                                        create_type=False,),
                                    nullable=False,
                                    default="queued",
                                    )
    result: Mapped[dict | None] = mapped_column(JSONB, nullable=True)
    error: Mapped[str | None ] = mapped_column(Text, nullable=True)
    attempts: Mapped[int] = mapped_column(SmallInteger, nullable=False, default=0)
    locked_by: Mapped[str | None] = mapped_column(Text, nullable=True)



    created_at = mapped_column(DateTime(timezone=True), server_default=func.now())
    started_at = mapped_column(DateTime(timezone=True), nullable=True)
    finished_at = mapped_column(DateTime(timezone=True), nullable=True)
