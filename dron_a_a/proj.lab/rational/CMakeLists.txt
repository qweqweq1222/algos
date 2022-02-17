cmake_minimum_required(VERSION 3.21)
project(520_B)

set(CMAKE_CXX_STANDARD 14)
include_directories(.)
add_library(rational rational.h rational.cpp)

add_executable(test test.cpp )

target_link_libraries(test rational)