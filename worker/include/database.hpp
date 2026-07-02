#pragma once

#include <pqxx/pqxx>
#include "job.hpp"



class Database {
private:
    std::unique_ptr<pqxx::connection>db;
public:
    explicit Database(const std::string& connection_string);

    std::optional<Job> fetch_next_job(const std::string& worker_id);
    void mark_job_succeeded(int job_id, const std::string& result);
    void mark_job_failed(int job_id, const std::string& error);

};