
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

add_library( ${target} ${src_lib} ${inc_lib})
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

	file(GLOB subdir "examples/*")
	
	#message(STATUS "list subdir : ${subdir}")
		
	set(list_of_dirs "")
	foreach(dir ${subdir})
		#message(STATUS "checking dir : examples/${dir}")
		if(IS_DIRECTORY ${dir})
			#message(STATUS "found new dir : ${dir}")
			set(list_of_dirs ${list_of_dirs} ${dir})
		endif()
	endforeach()

	foreach (dir ${list_of_dirs})
	
		file(GLOB list_srcs "${dir}/*.cpp")
		file(GLOB list_hdrs "${dir}/*.hpp")
	
		foreach (first_name ${list_srcs})
			string(REGEX REPLACE "^.*/(.+)/.+.cpp" "\\1" ex_name ${first_name})
			break()
		endforeach()
		
		message(STATUS "")
		message(STATUS "added new project : ${ex_name}")
		#message(STATUS "files : ${list_srcs}")
		message(STATUS "")
		
		add_executable( ${ex_name} ${list_srcs} ${list_hdrs} )
		target_link_libraries( ${ex_name} "pat" )
		
	endforeach()

endif()
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
