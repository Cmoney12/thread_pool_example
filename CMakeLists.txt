cmake_minimum_required(VERSION 3.20)
project(thread_pool)

set(CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(thread_pool main.cpp)
target_link_libraries(thread_pool Threads::Threads)