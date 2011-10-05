cmake_minimum_required(VERSION 2.8)

set(target "stereobp" )

project( ${target} )

find_package( OpenCV REQUIRED )
set(CMAKE_BUILD_TYPE "Debug")

file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.hpp")


if(UNIX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")
	set(CMAKE_CXX_FLAGS "-O0 -ggdb")
endif()

add_executable( ${target} ${srcs} ${hdrs})

target_link_libraries( ${target} ${OpenCV_LIBS})
