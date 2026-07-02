#include <chrono>
#include <csignal>
#include <atomic>
#include <thread>
#include <string>
#include <iostream>

#include "worker.hpp"
#include "job_executor.hpp"
#include "database.hpp"

std::atomic<bool> shutdown_requested{false};
void signal_handler(int){
    shutdown_requested.store(true);
}

int main() {
    std::signal(SIGINT, signal_handler);
    std::string conn_str =
        "host=localhost "
        "port=5433 "
        "dbname=jobrunner "
        "user=jobrunner "
        "password=local_dev_password";
    Database db{conn_str};
    JobExecutor executor;
    Worker worker{db, executor};

    std::thread worker_thread(&Worker::run, &worker);

    while (!shutdown_requested.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout<<"shutdown initiated\n";

    worker.stop();
    worker_thread.join();
    return 0;
}