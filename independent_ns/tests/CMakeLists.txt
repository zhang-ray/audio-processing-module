cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_CXX_STANDARD 14)

include_directories(../src)
add_executable(test_ns_00 test_00/test_00.cpp)

if(WIN32 OR ANDROID)
        target_link_libraries(test_ns_00 ns)
else(WIN32)
        target_link_libraries(test_ns_00 ns pthread)
endif(WIN32)


