cmake_minimum_required(VERSION 2.8)
set(target "pat_gui" )
project( ${target} )
set(CMAKE_BUILD_TYPE "Debug")

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.hpp")

qt4_wrap_cpp (MOC_SOURCES ${hdrs})

add_executable( ${target} ${srcs} ${hdrs} ${MOC_SOURCES})

target_link_libraries( ${target} ${QT_LIBRARIES})
