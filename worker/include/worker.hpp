#pragma once
#include <atomic>
#include <string>
#include "database.hpp"
#include "job_executor.hpp"

using namespace std::chrono_literals;

class Worker {
public:
    Worker(Database& database, JobExecutor& executor);

    void run();
    void stop();

private:
    Database& database;
    JobExecutor& executor;
    std::string generate_worker_id(std::size_t length =0);
    std::atomic<bool>stop_requested{false};
    std::string worker_id;
};