
cmake_minimum_required(VERSION 2.8.4)

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

set(target_console patgui)
add_executable(${target_console} ${console_srcs} ${console_hdrs} ${console_mocs_obj} ${qrc_sources} ${translations})
target_link_libraries(${target_console} ${QT_LIBRARIES} ${target_lib})

