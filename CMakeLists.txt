cmake_minimum_required(VERSION 3.20)
project(djs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(job
    src/job.cpp
)

target_include_directories(job
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(job_queue
    src/job_queue.cpp
)

target_include_directories(job_queue
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(djs
    src/main.cpp
)

target_link_libraries(djs
    PRIVATE
        job
)