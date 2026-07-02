#include "database.hpp"
#include <iostream>

Database::Database(const std::string& connection_string)
: db(std::make_unique<pqxx::connection>(connection_string)){
std::cout << "Connected to " << db->dbname() << '\n';
}

std::optional<Job> Database::fetch_next_job(const std::string& worker_id){
    pqxx::work tx(*db);

    pqxx::result result = tx.exec_params(R"(
        UPDATE jobs SET status = 'running',
        started_at = NOW(), locked_by= $1,
        attempts = attempts + 1
        WHERE job_id = (SELECT job_id FROM jobs
        WHERE status = 'queued'
        ORDER BY created_at FOR UPDATE SKIP LOCKED
        LIMIT 1) RETURNING job_id, job_type, payload;)", worker_id);
    if (result.empty()) {
        return std::nullopt;
    }

    pqxx::row row = result[0];

    Job job{
        row["job_id"].as<int>(),
        row["job_type"].as<std::string>(),
       row["payload"].as<std::string>()
      
    };
     tx.commit();

    return job;
}

void Database::mark_job_failed(int job_id, const std::string& error){
    pqxx::work tx(*db);

    tx.exec_params(
        R"(UPDATE jobs
           SET status='failed',
               locked_by=NULL,
               error=$1,
               finished_at=NOW()
           WHERE job_id=$2)",
        error,
        job_id);

    tx.commit();
}

void Database::mark_job_succeeded(int job_id, const std::string& result) {
    pqxx::work tx(*db);

    tx.exec_params(
        R"(UPDATE jobs
           SET status=$1,
               locked_by=NULL,
               result=$2::jsonb,
               finished_at=NOW()
           WHERE job_id=$3)",
        to_string(JobStatus::Succeeded),
        result,
        job_id);

    tx.commit();
}