
cmake_minimum_required(VERSION 2.8)

set(target "pat" )
project( ${target} )

# ----------------------------------------------------------------------------
# CONFIGURE
# ----------------------------------------------------------------------------

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(DEFINED CMAKE_BUILD_TYPE)
	set_property( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES} )
endif()

#set(CMAKE_BUILD_TYPE "Release")
#set(CMAKE_BUILD_TYPE "Debug")

# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
#  Get actual pat version number from sources
# ----------------------------------------------------------------------------
set(pat_version_file "${CMAKE_CURRENT_SOURCE_DIR}/include/pat/version.hpp")
file(STRINGS "${pat_version_file}" pat_version_parts REGEX "#define PAT_VERSION_.+[ ]+[0-9]+" )
string(REGEX REPLACE ".+PAT_VERSION_MAJOR[ ]+([0-9]+).*" "\\1"  PAT_VERSION_MAJOR  "${pat_version_parts}")
string(REGEX REPLACE ".+PAT_VERSION_MINOR[ ]+([0-9]+).*" "\\1"  PAT_VERSION_MINOR  "${pat_version_parts}")
string(REGEX REPLACE ".+PAT_VERSION_PATCH[ ]+([0-9]+).*" "\\1"  PAT_VERSION_PATCH  "${pat_version_parts}")
set(pat_version "${PAT_VERSION_MAJOR}.${PAT_VERSION_MINOR}.${PAT_VERSION_PATCH}")
# ----------------------------------------------------------------------------


set(PAT_CONFIG_FILE_INCLUDE_DIR "${CMAKE_BINARY_DIR}/" CACHE PATH "Where to create the platform-dependant patconfig.h")

message(STATUS "Parsing 'patconfig.h.cmake'")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/patconfig.h.cmake" "${PAT_CONFIG_FILE_INCLUDE_DIR}/patconfig.h")

# ---------------------------------------------------------------------------
# The C+//0 include & link directories:
# ---------------------------------------------------------------------------
include_directories("." "${PAT_CONFIG_FILE_INCLUDE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/include/pat")

# -------------------------------------------------------------------------------------------
#  Part 1/3: ${BIN_DIR}/PATConfig.cmake              -> For use *without* "make install"
# -------------------------------------------------------------------------------------------
set(CMAKE_INCLUDE_DIRS_CONFIGCMAKE "\"${PAT_CONFIG_FILE_INCLUDE_DIR}\" \"${CMAKE_CURRENT_SOURCE_DIR}/include\" \"${CMAKE_CURRENT_SOURCE_DIR}/include/pat\"")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib" CACHE PATH "Output directory for libraries" )
set(CMAKE_LIB_DIRS_CONFIGCMAKE "${LIBRARY_OUTPUT_PATH}")


file(GLOB src_lib "src/*.cpp")
file(GLOB inc_lib "include/pat/*.hpp")

find_package (Qt4 REQUIRED)
include_directories(${QT_INCLUDE_DIR})
set(CMAKE_INCLUDE_DIRS_CONFIGCMAKE "${CMAKE_INCLUDE_DIRS_CONFIGCMAKE} ${QT_INCLUDE_DIR}")
set(QT_LIBS ${QT_LIBRARIES})

add_library( ${target} ${src_lib} ${inc_lib} ${QT_LIBRARIES})

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/PATConfig.cmake.in" "${CMAKE_BINARY_DIR}/PATConfig.cmake" IMMEDIATE @ONLY)


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
message("    Configuration type : " ${CMAKE_BUILD_TYPE})
message("")
message("    C++ flags (Release): " ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE})
message("    C++ flags (Debug)  : " ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG})
message("")

# ----------------------------------------------------------------------------
