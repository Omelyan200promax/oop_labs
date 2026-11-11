cmake_minimum_required(VERSION 3.20)
project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Coverage flags
option(ENABLE_COVERAGE "Enable coverage" OFF)
if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Library (all cpp files)
file(GLOB_RECURSE LAB2_SOURCES "src/*.cpp")
add_library(lab2_lib ${LAB2_SOURCES})
target_include_directories(lab2_lib PUBLIC include)

# CLI
add_executable(lab2_cli app/main.cpp app/menu.cpp)
target_link_libraries(lab2_cli PRIVATE lab2_lib)

# Tests
enable_testing()
file(GLOB_RECURSE LAB2_TESTS "tests/*.cpp")
add_executable(lab2_tests ${LAB2_TESTS})
target_link_libraries(lab2_tests PRIVATE lab2_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab2_tests)