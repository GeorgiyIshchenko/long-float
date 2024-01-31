cmake_minimum_required(VERSION 3.26)
project(test)

set(CMAKE_CXX_STANDARD 20)

add_library(LongFloat src/LongFloat.cpp)
add_executable(test main.cpp)
target_link_libraries(test LongFloat)
