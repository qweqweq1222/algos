cmake_minimum_required(VERSION 3.21)
project(520_B)

set(CMAKE_CXX_STANDARD 14)
include_directories(.)
add_library(M3i M3i.h M3i.cpp)

add_executable(test test.cpp)

target_link_libraries(test M3i)