
status("")
status("General configuration for ${projectname} ${project_version}")
status("")
status("    Configuration type : " ${CMAKE_BUILD_TYPE} )
status("")
status("     C++ flags (common) : " ${CMAKE_CXX_FLAGS})
status("     C   flags (common) : " ${CMAKE_C_FLAGS})
status("     C++ flags (Release): " ${CMAKE_CXX_FLAGS_RELEASE})
status("     C++ flags (Debug)  : " ${CMAKE_CXX_FLAGS_DEBUG})

