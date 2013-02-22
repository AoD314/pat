cmake_minimum_required(VERSION 2.8.9)

find_package(PAT REQUIRED)
find_package(Qt4 REQUIRED)

add_executable(rozenbrok "rozenbrok.cpp")

target_link_libraries(rozenbrok ${PAT_LIBS})
