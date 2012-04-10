
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
