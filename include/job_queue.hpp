#pragma once
#include <mutex>
#include <condition_variable>
#include <queue>
#include "job.hpp"

class JobQueue {
public:
    JobQueue() = default;

    void push(const Job job);
    Job pop();
private:
    std::mutex mutex;
    std::condition_variable cv;
    std::queue<Job> jobs;
};