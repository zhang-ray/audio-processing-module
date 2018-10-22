cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_CXX_STANDARD 14)

if(WIN32)
    add_definitions(-DWEBRTC_DLL)
endif(WIN32)

include_directories(../src)
add_executable(test_00 test_00/test_00.cpp)

if(WIN32)
        target_link_libraries(test_00 vad)
else(WIN32)
        target_link_libraries(test_00 vad pthread)
endif(WIN32)


