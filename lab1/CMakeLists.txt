cmake_minimum_required(VERSION 3.10)
project(lab1)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab1 lab1.cpp extractnumber.cpp)


enable_testing()
add_executable(tests1 test_lab1.cpp  extractnumber.cpp)
target_link_libraries(tests1 ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND tests1)