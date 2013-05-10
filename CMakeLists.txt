cmake_minimum_required(VERSION 2.8.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(cmake/general.cmake)

clear_dependency()
add_dependency("qt4")

add_lib("pat" "pat/src/lib" "pat/include")
create_config("patconfig.hpp")
create_cmake_module("pat")

add_dependency("pat")
add_app(pat_server "pat/src/server")

add_app("rozenbrok" "examples/rozenbrok")

set_solution("pat")
