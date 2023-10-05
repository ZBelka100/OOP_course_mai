cmake_minimum_required(VERSION 3.10)
project(lab2)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab2 lab2.cpp eleven.cpp)


enable_testing()
add_executable(tests2 test_lab2.cpp  eleven.cpp)
target_link_libraries(tests2 ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND tests2)