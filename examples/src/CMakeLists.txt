cmake_minimum_required(VERSION 2.8.9)

find_package(PAT REQUIRED)

add_executable("rozenbrok" "rozenbrok.cpp")

target_link_libraries( ${target} ${PAT_LIBS})
