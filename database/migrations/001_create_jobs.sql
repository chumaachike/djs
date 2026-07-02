CREATE TYPE status AS ENUM (
    'queued',
    'running',
    'succeeded',
    'failed',
    'cancelled'
);

CREATE TABLE IF NOT EXISTS jobs (
    job_id BIGSERIAL PRIMARY KEY,
    job_type TEXT NOT NULL,
    payload JSONB NOT NULL,
    status status NOT NULL DEFAULT 'queued',
    result JSONB,
    error TEXT,
    attempts INT NOT NULL DEFAULT 0,
    locked_by TEXT,
    created_at TIMESTAMPTZ NOT NULL DEFAULT NOW(),
    started_at TIMESTAMPTZ,
    finished_at TIMESTAMPTZ
);

CREATE INDEX IF NOT EXISTS idx_jobs_queue
ON jobs(status, created_at);