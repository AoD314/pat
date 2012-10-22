
cmake_minimum_required(VERSION 2.8.9)

project(pat)

include(cmake/req.cmake)

include(cmake/compilers.cmake)

include(cmake/docs.cmake)

include(cmake/config.cmake)

include(cmake/FindQt4.cmake)

## BUILD ##

add_subdirectory(lib)
add_subdirectory(console)

#set(BUILD_GUI false CACHE BOOL "Build with GUI")

#if(BUILD_GUI)
#    add_subdirectory(gui)
#endif()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/PATConfig.cmake.in" "${CMAKE_BINARY_DIR}/PATConfig.cmake" IMMEDIATE @ONLY)

include(cmake/post_build.cmake)

include(cmake/install.cmake)

# ----------------------------------------------------------------------------
# STATUS
# ----------------------------------------------------------------------------

message(STATUS "")
message(STATUS "General configuration for pat ${pat_version} =====================================")
message(STATUS "")
message(STATUS "    Configuration type : " ${CMAKE_BUILD_TYPE} )
message(STATUS "")
message(STATUS "    C++ flags (common) : " ${CMAKE_CXX_FLAGS} )
message(STATUS "    C++ flags (Release): " ${CMAKE_CXX_FLAGS_RELEASE})
message(STATUS "    C++ flags (Debug)  : " ${CMAKE_CXX_FLAGS_DEBUG} )
message(STATUS "")

# ----------------------------------------------------------------------------
