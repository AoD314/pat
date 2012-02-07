add_library( ${target_lib} SHARED ${lib_srcs} ${lib_hdrs} ${lib_mocs_obj})
target_link_libraries( ${target_lib} ${QT_LIBRARIES})

if(WIN32)
	#add_definitions   (-DPATAPI_EXPORTS)
	#remove_definitions(-DPATAPI_IMPORTS)
	#set_target_properties(${target_lib} PROPERTIES DEFINE_SYMBOL PATAPI_EXPORTS)
endif()