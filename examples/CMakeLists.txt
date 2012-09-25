
cmake_minimum_required(VERSION 2.8)

project("examples")

set(CMAKE_BUILD_TYPE "Debug")
if(UNIX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")
    set(CMAKE_CXX_FLAGS "-O0 -ggdb")
endif()

add_subdirectory("rozenbrok")

#add_subdirectory("stereo")

add_subdirectory("pd")

