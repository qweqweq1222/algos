project(m3i)
add_library(m3i M3i.cpp M3i.h)
add_executable(test_M3i test.cpp)
target_link_libraries(test_M3i m3i)