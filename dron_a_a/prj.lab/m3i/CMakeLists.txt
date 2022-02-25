project(M3i)
add_library(M3i M3i.cpp M3i.h)
add_executable(test test.cpp)
target_link_libraries(test M3i)