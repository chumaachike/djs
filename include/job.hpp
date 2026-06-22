#pragma once
#include <string>
#include <chrono>

using Clock = std::chrono::system_clock;
using Timstamp = Clock::time_point;

enum class Status{PENDING, RUNNING, SUCCEDED, FAILED, RETRYING, DEAD};

struct Job {
    std::string id;
    std::string command;
    Status status;
    Timstamp created_at = Clock::now();
    Timstamp started_at;
    int attempts;
    int max_retries;
};