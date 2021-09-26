cmake_minimum_required(VERSION 3.20)
project(run_unit_test)

include(FetchContent)

set(CMAKE_CXX_STANDARD 14)


FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
include(CTest)
enable_testing()
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(run_unit_test test.h test.cpp ${test_SRCS})

target_link_libraries(run_unit_test gtest_main)