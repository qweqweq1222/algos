project(rational)
add_library(rational rational.h rational.cpp)
add_executable(test test.cpp)
target_link_libraries(test rational)