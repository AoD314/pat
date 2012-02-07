#add_executable( ${target_gui} ${gui_srcs} ${gui_hdrs} ${gui_mocs_obj} ${qrc_sources} ${translations})
add_library(patgui ${gui_srcs} ${gui_hdrs} ${gui_mocs_obj} ${qrc_sources} ${translations})
target_link_libraries(patgui ${QT_LIBRARIES} ${target_lib})

#if(WIN32)
	#remove_definitions(-DPATAPI_EXPORTS)
	#add_definitions   (-DPATAPI_IMPORTS)	
	set_target_properties(patgui PROPERTIES DEFINE_SYMBOL PATAPI_MPORTS1)
#endif()