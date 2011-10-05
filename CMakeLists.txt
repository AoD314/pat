
cmake_minimum_required(VERSION 2.8)

set(target "pat" )
project( ${target} )
include_directories("include")

if(UNIX)
	#set(WARNING "-Wall -Wextra -Weffc++ -Wconversion -Wsign-conversion -Wold-style-cast ") # -Werror
	#set(WARNING "${WARNING} -Wunreachable-code -Woverloaded-virtual -Wctor-dtor-privacy ")
	set(CMAKE_CXX_FLAGS "${WARNING}")
	#set(CMAKE_CXX_FLAGS " -pg ")
	
	#set(CMAKE_CXX_FLAGS "-msse4.1 -msse4.2 ${WARNING}")
	
	#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wnon-virtual-dtor -foptimize-sibling-calls")
	#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -finline-functions -ftree-loop-optimize -floop-parallelize-all")
	#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pipe -fomit-frame-pointer ")
	#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")
endif()

file(GLOB src_lib "src/*.cpp")
file(GLOB inc_lib "include/pat/*.hpp")

find_package (Qt4 REQUIRED)
include (${QT_USE_FILE})

add_library( ${target} ${src_lib} ${inc_lib} ${QT_LIBRARIES})
#target_link_libraries( ${target} )

# ----------------------------------------------------------------------------
# CONFIGURE
# ----------------------------------------------------------------------------

#set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "Debug")

# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
#  Get actual pat version number from sources
# ----------------------------------------------------------------------------
set(pat_version_file "${CMAKE_CURRENT_SOURCE_DIR}/include/pat/version.hpp")
file(STRINGS "${pat_version_file}" pat_version_parts REGEX "#define PAT_.+OR_VERSION[ ]+[0-9]+" )
string(REGEX REPLACE ".+PAT_MAJOR_VERSION[ ]+([0-9]+).*" "\\1"    PAT_MAJOR_VERSION    "${pat_version_parts}")
string(REGEX REPLACE ".+PAT_MINOR_VERSION[ ]+([0-9]+).*" "\\1"    PAT_MINOR_VERSION    "${pat_version_parts}")
string(REGEX REPLACE ".+PAT_SUBMINOR_VERSION[ ]+([0-9]+).*" "\\1" PAT_SUBMINOR_VERSION "${pat_version_parts}")
set(pat_version "${PAT_MAJOR_VERSION}.${PAT_MINOR_VERSION}.${PAT_SUBMINOR_VERSION}")
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# EXAMPLES
# ----------------------------------------------------------------------------

set(BUILD_EXAMPLES ON CACHE BOOL "Build all examples")

if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()

# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# gui
# ----------------------------------------------------------------------------

add_subdirectory(gui)

# ----------------------------------------------------------------------------


# ----------------------------------------------------------------------------
# INSTALL
# ----------------------------------------------------------------------------

if(UNIX)
	install(TARGETS ${target} DESTINATION "/usr/lib")
	find_path(LIB_INCLUDE_PATH string.h)
	install(FILES ${inc_lib} DESTINATION "${LIB_INCLUDE_PATH}/pat")
endif()

# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# STATUS
# ----------------------------------------------------------------------------
message("")
message("General configuration for pat ${pat_version} =====================================")
message("")
message("    Build all examples : " ${BUILD_EXAMPLES})
message("    Configuration type : " ${CMAKE_BUILD_TYPE})
message("")
message("    C++ flags (Release): " ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE})
message("    C++ flags (Debug)  : " ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG})
message("")

# ----------------------------------------------------------------------------
