#pragma once
#include <string>
#include <stdexcept>

struct Job {
    int id;
    std::string job_type;
    std::string payload;
};

enum class JobStatus {
    Queued,
    Running,
    Succeeded,
    Failed,
    Cancelled
};

inline std::string to_string(JobStatus status) {
    switch (status) {
        case JobStatus::Queued:
            return "queued";
        case JobStatus::Running:
            return "running";
        case JobStatus::Succeeded:
            return "succeeded";
        case JobStatus::Failed:
            return "failed";
        case JobStatus::Cancelled:
            return "cancelled";
    }

    throw std::runtime_error("Unknown JobStatus");
}