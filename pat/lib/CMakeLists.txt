
cmake_minimum_required(VERSION 2.8.4)

set(target patlib)

project(${target})

file(GLOB lib_srcs "src/*.cpp")

file(GLOB lib_hdrs "include/pat/*.hpp")

set(lib_mocs )

foreach(f ${lib_hdrs})
    check_moc(${f})
    if(${MOC_FILE})
        set(lib_mocs ${lib_mocs} ${f})
    endif()
endforeach()

#message(STATUS "srcs: ${lib_srcs}")
#message(STATUS "hdrs: ${lib_hdrs}")
#message(STATUS "mocs: ${lib_mocs}")

qt4_wrap_cpp(lib_mocs_obj ${lib_mocs})

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_SHARED)

add_library(${target} SHARED ${lib_srcs} ${lib_hdrs} ${lib_mocs_obj})
target_link_libraries(${target} ${QT_LIBRARIES})
