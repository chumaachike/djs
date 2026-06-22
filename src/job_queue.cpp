#include "job_queue.hpp"

void JobQueue::push(const Job job){
    {
        std::lock_guard lock (mutex);
        jobs.push(job);
    }
    cv.notify_one();
}

Job JobQueue::pop(){
    std::unique_lock lock (mutex);
    cv.wait(lock, [this] {return !jobs.empty();});
    auto job = jobs.front();
    jobs.pop();
    return job;
}