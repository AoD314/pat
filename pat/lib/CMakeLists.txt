
cmake_minimum_required(VERSION 2.8.4)

file(GLOB lib_srcs "src/*.cpp")

file(GLOB lib_hdrs "src/pat/*.hpp")

file(GLOB lib_mocs  "include/pat/algorithm.hpp"
                    "include/pat/alg_bruteforce.hpp"
                    "include/pat/alg_gradient.hpp"
                    "include/pat/alg_rnd.hpp"
                    "include/pat/alg_downhill_simplex.hpp"
)

set(lib_hdrs ${lib_hdrs} ${lib_mocs})

qt4_wrap_cpp(lib_mocs_obj ${lib_mocs})

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_SHARED)

set(target_lib "patlib")

add_library(${target_lib} SHARED ${lib_srcs} ${lib_hdrs} ${lib_mocs_obj})

target_link_libraries(${target_lib} ${QT_LIBRARIES})
