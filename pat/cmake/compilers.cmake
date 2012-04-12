

# ----------------------------------------------------------------------------
# FLAGS
# ----------------------------------------------------------------------------

# -Wall -Wextra -pedantic -Weffc++ -Wconversion -Wsign-conversion -Wold-style-cast -Wunreachable-code -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

# ----------------------------------------------------------------------------
