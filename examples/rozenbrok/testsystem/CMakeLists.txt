cmake_minimum_required(VERSION 2.8)

set(target "ts_rosenbrok" )
project( ${target} )

find_package( PAT REQUIRED )

file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.hpp")

add_executable( ${target} ${srcs} ${hdrs} )

target_link_libraries( ${target} ${PAT_LIBS})

