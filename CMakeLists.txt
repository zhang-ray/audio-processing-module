cmake_minimum_required(VERSION 3.5.0)
project(audio-processing-module) # audio processing module
#add_subdirectory (src)
add_subdirectory(independent_vad)
add_subdirectory(independent_ns)
add_subdirectory(independent_aec)
