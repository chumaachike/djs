cmake_minimum_required(VERSION 3.20)
project(djs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(scheduler
    src/main.cpp
    src/job_queue.cpp
)

target_include_directories(scheduler PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)