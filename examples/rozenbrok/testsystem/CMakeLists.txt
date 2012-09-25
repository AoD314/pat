cmake_minimum_required(VERSION 2.8)

set(target "ts_rosenbrok" )
project( ${target} )

#set(CMAKE_VERBOSE_MAKEFILE ON)

find_package( PAT REQUIRED )

find_package(Qt4 4.7.0 COMPONENTS QtCore QtGui QtNetwork REQUIRED)
include(${QT_USE_FILE})
include_directories( ${QT_INCLUDE_DIR} )
set(CMAKE_INCLUDE_DIRS_CONFIGCMAKE "${CMAKE_INCLUDE_DIRS_CONFIGCMAKE} ${QT_INCLUDE_DIR}")


file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.hpp")

add_executable( ${target} ${srcs} ${hdrs} )

target_link_libraries( ${target} ${PAT_LIBS} ${QT_LIBRARIES})

