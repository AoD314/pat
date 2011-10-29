
cmake_minimum_required(VERSION 2.8)

set(target_lib "pat" )
set(target_gui "pat_gui" )
project( ${target_lib} )

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

set(PAT_CONFIG_FILE_INCLUDE_DIR "${CMAKE_BINARY_DIR}/" CACHE PATH "Where to create the platform-dependant patconfig.hpp")

message(STATUS "Parsing 'patconfig.h.cmake'")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/patconfig.h.cmake" "${PAT_CONFIG_FILE_INCLUDE_DIR}/patconfig.hpp")

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

# ---------------------------------------------------------------------------
# BUILD
# ---------------------------------------------------------------------------

find_package(Qt4 4.7.0 COMPONENTS QtCore QtGui QtNetwork REQUIRED)
include(${QT_USE_FILE})
include_directories( ${QT_INCLUDE_DIR} )
set(CMAKE_INCLUDE_DIRS_CONFIGCMAKE "${CMAKE_INCLUDE_DIRS_CONFIGCMAKE} ${QT_INCLUDE_DIR}")
set(QT_LIBS ${QT_LIBRARIES})

### LIB ###

set(lib_srcs "src/pat_base.cpp"
             "src/pat_convert.cpp"
			 "src/pat_params.cpp"
			 "src/pat_system.cpp"
    )
	
set(lib_hdrs "include/pat/pat.hpp"
             "include/pat/pat_base.hpp"
			 "include/pat/pat_convert.hpp"
			 "include/pat/pat_params.hpp"
			 "include/pat/pat_record_params.hpp"
			 "include/pat/pat_system.hpp"
             "include/pat/version.hpp"
    )

### GUI ###
	
set(gui_srcs "src/gui_bruteforce.cpp"
             "src/gui_main.cpp"
             "src/gui_mainwindow.cpp"
			 "src/gui_server.cpp"
    )
	
set(gui_hdrs "")

set(gui_mocs "include/pat/gui_alg_bruteforce.hpp"
             "include/pat/gui_algorithm.hpp"
             "include/pat/gui_mainwindow.hpp"
			 "include/pat/gui_server.hpp"
    )

qt4_wrap_cpp(gui_mocs_obj ${gui_mocs})

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_SHARED)

if (WIN32)
	add_definitions(-DPATAPI_EXPORTS)
endif()

add_library( ${target_lib} SHARED ${lib_srcs} ${lib_hdrs})
target_link_libraries( ${target_lib} ${QT_LIBRARIES})

if (WIN32)
	#remove_definitions(-DPATAPI_EXPORTS)
endif()

add_executable( ${target_gui} ${gui_srcs} ${gui_hdrs} ${gui_mocs_obj})
target_link_libraries( ${target_gui} ${QT_LIBRARIES} ${target_lib})

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/PATConfig.cmake.in" "${CMAKE_BINARY_DIR}/PATConfig.cmake" IMMEDIATE @ONLY)

# ----------------------------------------------------------------------------
# post build event
# ----------------------------------------------------------------------------
add_custom_command( TARGET ${target_lib} POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin)
if (UNIX)
	add_custom_command( TARGET ${target_lib} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_OUTPUT_PATH}/libpat.* ${CMAKE_BINARY_DIR}/bin)
	add_custom_command( TARGET ${target_gui} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/pat_gui ${CMAKE_BINARY_DIR}/bin)
else()
	add_custom_command( TARGET ${target_lib} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_OUTPUT_PATH}/$(ConfigurationName)/pat.dll ${CMAKE_BINARY_DIR}/bin)
	add_custom_command( TARGET ${target_lib} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_OUTPUT_PATH}/$(ConfigurationName)/pat.lib ${CMAKE_BINARY_DIR}/bin)
	add_custom_command( TARGET ${target_gui} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/$(ConfigurationName)/pat_gui.exe ${CMAKE_BINARY_DIR}/bin)
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
message("    Configuration type : " ${CMAKE_BUILD_TYPE})
message("")
message("    C++ flags (Release): " ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE})
message("    C++ flags (Debug)  : " ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG})
message("")

# ----------------------------------------------------------------------------
