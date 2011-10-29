cmake_minimum_required(VERSION 2.8)
set(target "stereobp" )
project( ${target} )

set(CMAKE_BUILD_TYPE "Debug")
if(UNIX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")
	set(CMAKE_CXX_FLAGS "-O0 -ggdb")
endif()

find_package( OpenCV REQUIRED )
find_package( PAT REQUIRED )

file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.hpp")

add_executable( ${target} ${srcs} ${hdrs})

target_link_libraries( ${target} ${OpenCV_LIBS} ${PAT_LIBS})

# ----------------------------------------------------------------------------
# post build event
# ----------------------------------------------------------------------------

add_custom_command( TARGET ${target} COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin)

if (UNIX)
	add_custom_command( TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/stereo/app/${target} ${CMAKE_BINARY_DIR}/bin)
else()
	add_custom_command( TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/stereo/app/$(ConfigurationName)/stereobp.exe ${CMAKE_BINARY_DIR}/bin)
endif()

# ----------------------------------------------------------------------------
