cmake_minimum_required(VERSION 2.8)
set(target "testsystem" )
project( ${target} )

set(CMAKE_BUILD_TYPE "Debug")
if(UNIX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")
	set(CMAKE_CXX_FLAGS "-O0 -ggdb")
endif()

find_package( OpenCV REQUIRED )
if(WIN32)
	link_directories("${OPENCV_LIB_DIR}/${CMAKE_BUILD_TYPE}")
endif()

find_package( PAT REQUIRED )

file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.hpp")

add_executable( ${target} ${srcs} ${hdrs} )

target_link_libraries( ${target} ${OpenCV_LIBS} ${PAT_LIBS})

# ----------------------------------------------------------------------------
# post build event
# ----------------------------------------------------------------------------

add_custom_command( TARGET ${target} COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin)
add_custom_command( TARGET ${target} COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/stereo/testsystem/${target} ${CMAKE_BINARY_DIR}/bin)

add_custom_command( TARGET ${target} COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/stereo/dataset/aloe_gl.png ${CMAKE_BINARY_DIR}/bin)
add_custom_command( TARGET ${target} COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/stereo/dataset/aloe_gr.png ${CMAKE_BINARY_DIR}/bin)
add_custom_command( TARGET ${target} COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/stereo/dataset/aloe_l.png ${CMAKE_BINARY_DIR}/bin)
add_custom_command( TARGET ${target} COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/stereo/dataset/aloe_r.png ${CMAKE_BINARY_DIR}/bin)

# ----------------------------------------------------------------------------
