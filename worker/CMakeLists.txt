cmake_minimum_required(VERSION 3.20)
project(worker LANGUAGES CXX)

# Match the distro's pre-compiled standard (fixes the linker error)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(PostgreSQL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(libpqxx REQUIRED IMPORTED_TARGET libpqxx)

# 1. Define the internal library target correctly
add_library(worker_lib STATIC 
    src/database.cpp
    src/job_executor.cpp
    src/worker.cpp
)

# 2. Tell the library where its public headers are
target_include_directories(worker_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 3. Link DB dependencies to the library (if job_fetcher.cpp uses libpqxx/PostgreSQL)
target_link_libraries(worker_lib PUBLIC
    PkgConfig::libpqxx
    PostgreSQL::PostgreSQL
)
# 4. Define the executable
add_executable(work src/main.cpp)

# 5. Link the executable to your internal library
target_link_libraries(work PRIVATE worker_lib)
