cmake_minimum_required(VERSION 2.8)

set(target "ts_stereo" )
project( ${target} )

find_package( OpenCV REQUIRED )
find_package( PAT REQUIRED )

file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.hpp")

add_executable( ${target} ${srcs} ${hdrs} )

target_link_libraries( ${target} ${OpenCV_LIBS} ${PAT_LIBS})

# ----------------------------------------------------------------------------
# post build event
# ----------------------------------------------------------------------------

add_custom_command( TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin)

if (UNIX)
	add_custom_command( TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/stereo/testsystem/${target} ${CMAKE_BINARY_DIR}/bin)
else()
	add_custom_command( TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/stereo/testsystem/$(ConfigurationName)/{target}.exe ${CMAKE_BINARY_DIR}/bin)
endif()

add_custom_command( TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/stereo/dataset/aloe_gl.png ${CMAKE_BINARY_DIR}/bin)
add_custom_command( TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/stereo/dataset/aloe_gr.png ${CMAKE_BINARY_DIR}/bin)
add_custom_command( TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/stereo/dataset/aloe_l.png ${CMAKE_BINARY_DIR}/bin)
add_custom_command( TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/stereo/dataset/aloe_r.png ${CMAKE_BINARY_DIR}/bin)

add_custom_command( TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/stereo/dataset/baby_gl.png ${CMAKE_BINARY_DIR}/bin)
add_custom_command( TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/stereo/dataset/baby_gr.png ${CMAKE_BINARY_DIR}/bin)
add_custom_command( TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/stereo/dataset/baby_l.png ${CMAKE_BINARY_DIR}/bin)
add_custom_command( TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/stereo/dataset/baby_r.png ${CMAKE_BINARY_DIR}/bin)
# ----------------------------------------------------------------------------
