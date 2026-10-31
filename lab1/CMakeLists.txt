cmake_minimum_required(VERSION 3.20)
project(lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка покрытия (передается из CI через -DENABLE_COVERAGE=ON)
option(ENABLE_COVERAGE "Enable coverage" OFF)
if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Статическая сборка для Windows (чтобы .exe запускался без DLL)
if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

# GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Библиотека предметной области
add_library(lab1_lib
    src/Atom.cpp
    src/Set.cpp
    src/MultiSet.cpp
)
target_include_directories(lab1_lib PUBLIC include)

# CLI
add_executable(lab1_cli
    app/main.cpp
    app/menu.cpp
)
target_link_libraries(lab1_cli PRIVATE lab1_lib)

# Тесты
enable_testing()

add_executable(lab1_tests
    tests/AtomTest.cpp
    tests/SetTest.cpp
    tests/MultiSetTest.cpp
)
target_link_libraries(lab1_tests PRIVATE lab1_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab1_tests)