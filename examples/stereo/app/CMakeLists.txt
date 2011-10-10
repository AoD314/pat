cmake_minimum_required(VERSION 2.8)

set(target "stereobp" )

project( ${target} )

set(CMAKE_BUILD_TYPE "Debug")
if(UNIX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")
	set(CMAKE_CXX_FLAGS "-O0 -ggdb")
endif()

file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.hpp")

add_executable( ${target} ${srcs} ${hdrs})

find_package( OpenCV REQUIRED )
link_directories(${OPENCV_LIB_DIR})

find_package( PAT REQUIRED )

message("${OpenCV_LIBS}")
message("${OpenCV_LIB_DIR}")
message("${PAT_LIBS}")

target_link_libraries( ${target} ${OpenCV_LIBS} ${PAT_LIBS})
