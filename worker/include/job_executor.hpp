#pragma once
#include <string>
#include <optional>
#include <nlohmann/json.hpp>
#include "job.hpp"

using json = nlohmann::json;
class JobExecutor {
public:
    std::optional<std::string> execute(const Job& job);
private:
    std::optional<std::string> execute_factorial(const std::string& payload);
    std::optional<std::string> execute_sleep(const std::string& payload);
};