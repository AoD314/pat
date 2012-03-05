cmake_minimum_required(VERSION 2.8)

set(target "testsystem" )
project( ${target} )

set(CMAKE_BUILD_TYPE "Debug")
if(UNIX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")
	set(CMAKE_CXX_FLAGS "-O0 -ggdb")
endif()

find_package( PAT REQUIRED )

file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.hpp")

add_executable( ${target} ${srcs} ${hdrs} )

target_link_libraries( ${target} ${OpenCV_LIBS} ${PAT_LIBS})

