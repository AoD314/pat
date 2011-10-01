cmake_minimum_required(VERSION 2.8)

set(target "stereobp" )

project( ${target} )

find_package( OpenCV REQUIRED )
set(CMAKE_BUILD_TYPE "Release")

file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.hpp")

add_executable( ${target} ${srcs} ${hdrs})

target_link_libraries( ${target} ${OpenCV_LIBS})
