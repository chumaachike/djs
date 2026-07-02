#include <thread>
#include <random>
#include <unistd.h>

#include "worker.hpp"

Worker::Worker(Database& database, JobExecutor& executor)
    :database(database), executor(executor){
        worker_id = "worker-" + generate_worker_id() + "-" + std::to_string(getpid());
    }
void Worker::run(){
    while (!stop_requested){
        auto job = database.fetch_next_job(worker_id);
        if (!job.has_value()){
            std::this_thread::sleep_for(200ms);
            continue;
        }
        auto result = executor.execute(*job);

        if (result.has_value()) {
            database.mark_job_succeeded(job->id, *result);
        } else {
            database.mark_job_failed(job->id, "Invalid job type or payload");
        }
    }
}

void Worker::stop(){
    stop_requested.store(true);
}

std::string Worker::generate_worker_id(std::size_t length){
    static constexpr char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0, sizeof(charset) - 2);

    std::string id;
    id.reserve(length);

    for (std::size_t i = 0; i < length; ++i) {
        id += charset[dist(gen)];
    }

    return id;

}