#include <thread>
#include <chrono>
#include "job_executor.hpp"

std::optional<std::string> JobExecutor::execute(const Job& job){
    if (job.job_type == "sleep"){
        return execute_sleep(job.payload);
    }else if (job.job_type == "factorial") {
        return execute_factorial(job.payload);
    
    }else{
        return std::nullopt;
    }
}


std::optional<std::string> JobExecutor::execute_factorial(const std::string& payload) {
    try {
        auto json_payload = json::parse(payload);

        if (!json_payload.contains("n") || !json_payload["n"].is_number_integer()) {
            return std::nullopt;
        }

        int n = json_payload["n"].get<int>();

        if (n < 0 || n > 20) {
            return std::nullopt;
        }
        unsigned long long result = 1;

        for (int i = 1; i <= n; ++i) {
            result *= i;
        }

        json response;
        response["result"] = result;
        return response.dump();

    } catch (const json::parse_error&) {
        return std::nullopt;
    }
}

std::optional<std::string> JobExecutor::execute_sleep(const std::string& payload) {
    try {
        auto json_payload = json::parse(payload);

        if (!json_payload.contains("seconds") ||
            !json_payload["seconds"].is_number_integer()) {
            return std::nullopt;
        }

        int seconds = json_payload["seconds"].get<int>();

        if (seconds < 0) {
            return std::nullopt;
        }

        std::this_thread::sleep_for(std::chrono::seconds(seconds));

        json response;
        response["slept_s"] = seconds;
        return response.dump();

    } catch (const json::parse_error&) {
        return std::nullopt;
    }
}