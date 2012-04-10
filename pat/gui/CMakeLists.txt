
cmake_minimum_required(VERSION 2.8.4)

#file(GLOB gui_srcs "src/*.cpp")
#file(GLOB gui_srcs "src/pat/*.hpp")

set(gui_srcs "main.cpp"
             "mainwindow.cpp"
             "settingswindow.cpp"
             "algwindow.cpp"
             "server.cpp"
             "common.cpp"
             "paramstatus.cpp"
)

set(gui_hdrs "common.hpp")

set(gui_mocs "mainwindow.hpp"
             "settingswindow.hpp"
             "algwindow.hpp"
             "server.hpp"
             "paramstatus.hpp"
)

set(gui_hdrs ${gui_hdrs} ${gui_mocs})

qt4_wrap_cpp(gui_mocs_obj ${gui_mocs})

qt4_add_resources(qrc_sources ${RESOURCES})

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_SHARED)

set(target_gui patgui)
add_executable(${target_gui} ${gui_srcs} ${gui_hdrs} ${gui_mocs_obj} ${qrc_sources} ${translations})
target_link_libraries(${target_gui} ${QT_LIBRARIES} ${target_lib})
