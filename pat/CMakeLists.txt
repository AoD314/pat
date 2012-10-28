
cmake_minimum_required(VERSION 2.8.9)

# Add directory to CMake's module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
include(cmake/project_utils.cmake)
include(cmake/compilers.cmake)
include(cmake/pat_version.cmake)
include(cmake/doc.cmake)

set_project("pat")
set_dependency("qt4")

include(cmake/config.cmake)

add_subdirectory(lib)
add_subdirectory(app)

include(cmake/post_build.cmake)
include(cmake/install.cmake)
include(cmake/status.cmake)
