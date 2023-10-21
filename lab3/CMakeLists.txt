cmake_minimum_required(VERSION 3.10)
project(lab3)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab3 lab3.cpp point.cpp figure.cpp figure_arr.cpp triangle.cpp square.cpp rectangle.cpp)

enable_testing()
add_executable(tests3 test_lab3.cpp point.cpp figure.cpp figure_arr.cpp triangle.cpp square.cpp rectangle.cpp)
target_link_libraries(tests3 ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND tests3)