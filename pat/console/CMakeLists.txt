
cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_BUILD_TYPE "Debug")

file(GLOB console_srcs "src/*.cpp")
file(GLOB console_hdrs "src/*.hpp")

set(console_mocs )

set(console_hdrs ${console_hdrs} ${console_mocs})

qt4_wrap_cpp(console_mocs_obj ${console_mocs})

qt4_add_resources(qrc_sources ${RESOURCES})

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_SHARED)

add_executable(pat_console ${console_srcs} ${console_hdrs} ${console_mocs_obj} ${qrc_sources} ${translations})
target_link_libraries(pat_console ${QT_LIBRARIES} patlib)
