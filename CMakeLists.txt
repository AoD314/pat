
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
# DOCUMENTATION
# ----------------------------------------------------------------------------

set(ENABLE_DOCS OFF CACHE BOOL "Enable build documentation")
if (ENABLE_DOCS)
		add_subdirectory(doc)
endif()

# ----------------------------------------------------------------------------







# ----------------------------------------------------------------------------
#  Get actual pat version number from sources
# ----------------------------------------------------------------------------
set(pat_version_file "${CMAKE_CURRENT_SOURCE_DIR}/lib/include/pat/version.hpp")
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

include_directories("." "${PAT_CONFIG_FILE_INCLUDE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/lib/include" "${CMAKE_CURRENT_SOURCE_DIR}/lib/include" "${CMAKE_CURRENT_SOURCE_DIR}/common")

# -------------------------------------------------------------------------------------------
#  Part 1/3: ${BIN_DIR}/PATConfig.cmake              -> For use *without* "make install"
# -------------------------------------------------------------------------------------------
set(CMAKE_INCLUDE_DIRS_CONFIGCMAKE "\"${PAT_CONFIG_FILE_INCLUDE_DIR}\" \"${CMAKE_CURRENT_SOURCE_DIR}/include\" \"${CMAKE_CURRENT_SOURCE_DIR}/lib/include\" \"${CMAKE_CURRENT_SOURCE_DIR}/common\"")
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

set(lib_srcs "lib/src/pat_base.cpp"
             "lib/src/pat_convert.cpp"
             "lib/src/pat_params.cpp"
             "lib/src/alg_bruteforce.cpp"
             "lib/src/alg_gradient.cpp"
             "lib/src/pat_strparam.cpp"
             "lib/src/pat_system.cpp"
    )

set(lib_hdrs "lib/include/pat/pat.hpp"
             "lib/include/pat/pat_base.hpp"
             "lib/include/pat/pat_convert.hpp"
             "lib/include/pat/pat_params.hpp"
             "lib/include/pat/pat_record_params.hpp"
             "lib/include/pat/pat_system.hpp"
             "lib/include/pat/pat_strparam.hpp"
             "lib/include/pat/version.hpp"
    )

set(lib_mocs "lib/include/pat/algorithm.hpp"
             "lib/include/pat/alg_bruteforce.hpp"
             "lib/include/pat/alg_gradient.hpp"
    )
### COMMON ###

set(common_hdrs "common/settings.hpp")
set(common_srcs "common/settings.cpp")

### GUI ###

set(gui_srcs 
             "gui/main.cpp"
             "gui/mainwindow.cpp"
             "gui/settingswindow.cpp"
             "gui/algwindow.cpp"
             "gui/server.cpp"
             "gui/common.cpp"
             "gui/paramstatus.cpp"
             "common/settings.cpp" 
    )

set(gui_hdrs "common/settings.hpp"
             "gui/common.hpp")

set(gui_mocs 
             "gui/mainwindow.hpp"
             "gui/settingswindow.hpp"
             "gui/algwindow.hpp"
             "gui/server.hpp"
             "gui/paramstatus.hpp"
    )

### CONSOLE ###


### LANGUAGE ###

set (RESOURCES resources/resources.qrc)
set (TRANSLATIONSATIONS_PATH ../resources/translations)

set (LANGUAGES ru)

foreach (LANGUAGE ${LANGUAGES})
    set (TS ${TRANSLATIONS_PATH}/${LANGUAGE}.ts)
    set (QM ${TRANSLATIONS_PATH}/${LANGUAGE}.qm)
    set (TRANSLATIONSATIONS_PATHNS ${TRANSLATIONS} ${TS})
    set (TRANSLATIONS_BINARY ${TRANSLATIONS_BINARYRY} ${QM})
    add_custom_command (
        OUTPUT ${QM}
        COMMAND ${QT_LRELEASE_EXECUTABLE_EXECUTABLE} ${TS}
        MAIN_DEPENDENCY ${TS})
endforeach()

add_custom_target (translations COMMAND ${QT_LUPDATE_EXECUTABLE} ${HEADERS} ${SOURCES} -ts ${TRANSLATIONS})
add_custom_command ( TARGET translations COMMAND ${QT_LRELEASE_EXECUTABLE} ${TRANSLATIONS})

################

set(gui_hdrs ${gui_hdrs} ${gui_mocs} ${common_hdrs})
set(lib_hdrs ${lib_hdrs} ${lib_mocs} ${common_hdrs})

qt4_wrap_cpp(gui_mocs_obj ${gui_mocs})
qt4_wrap_cpp(lib_mocs_obj ${lib_mocs})

qt4_add_resources (qrc_sources ${RESOURCES})

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_SHARED)

if (WIN32)
	add_definitions(-DPATAPI_EXPORTS)
endif()

add_library( ${target_lib} SHARED ${lib_srcs} ${lib_hdrs} ${lib_mocs_obj})
target_link_libraries( ${target_lib} ${QT_LIBRARIES})

add_executable( ${target_gui} ${gui_srcs} ${gui_hdrs} ${gui_mocs_obj} ${qrc_sources} ${translations})
target_link_libraries( ${target_gui} ${QT_LIBRARIES} ${target_lib})




configure_file("${CMAKE_CURRENT_SOURCE_DIR}/PATConfig.cmake.in" "${CMAKE_BINARY_DIR}/PATConfig.cmake" IMMEDIATE @ONLY)

# ----------------------------------------------------------------------------
# post build event
# ----------------------------------------------------------------------------
add_custom_command( TARGET ${target_lib} POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin)
add_custom_command( TARGET ${target_lib} POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/trans)
add_custom_command( TARGET ${target_lib} POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/trans)

foreach (LANGUAGE ${LANGUAGES})
    set (TS ${TRANSLATIONS_PATH}/${LANGUAGESAGE}.ts)
    add_custom_command( TARGET ${target_gui} POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/translations/${LANGUAGE}.qm ${CMAKE_BINARY_DIR}/trans)
    add_custom_command( TARGET ${target_gui} POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/translations/${LANGUAGE}.qm
        ${CMAKE_BINARY_DIR}/bin/trans)
endforeach()

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
