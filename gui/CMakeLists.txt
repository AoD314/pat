cmake_minimum_required(VERSION 2.8)
set(target "pat_gui" )
project( ${target} )
set(CMAKE_BUILD_TYPE "Debug")

#set (RESOURCE_PATH  resources)
#set (RESOURCES ${RESOURCE_PATH}/resources.qrc)
#set (TRANSLATIONS_PATH resources/translations)

find_package (Qt4 REQUIRED)
include (${QT_USE_FILE})

file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.hpp")

#qt4_add_resources (QRC_SOURCES ${RESOURCES})
#qt4_wrap_cpp (MOC_SOURCES ${hdrs})

#set (LANGUAGES rus eng)
#set (LANGUAGES "")

#foreach (LANGUAGE ${LANGUAGES})
#	set (TS ${TRANSLATIONS_PATH}/${LANGUAGE}.ts)
#	set (QM ${TRANSLATIONS_PATH}/${LANGUAGE}.qm)
#	set (TRANSLATIONS ${TRANSLATIONS} ${TS})
#	set (TRANSLATIONS_BINARY ${TRANSLATIONS_BINARY} ${QM})
#	add_custom_command ( OUTPUT ${QM} COMMAND ${QT_LRELEASE_EXECUTABLE} ${TS} MAIN_DEPENDENCY ${TS})
#endforeach()

#add_custom_target  ( translations COMMAND ${QT_LUPDATE_EXECUTABLE} ${HEADERS} ${SOURCES} -ts ${TRANSLATIONS}) 
#add_custom_command ( TARGET translations COMMAND ${QT_LRELEASE_EXECUTABLE} ${TRANSLATIONS})

#source_group ("Header Files" FILES ${hrds})
#source_group ("Source Files" FILES ${srcs})
#source_group ("Generated Files" FILES ${MOC_SOURCES})
#source_group ("Resource Files" FILES ${QRC_SOURCES})

add_executable( ${target} ${srcs} ${hdrs})# ${MOC_SOURCES} ${QRC_SOURCES} ${TRANSLATIONS})
target_link_libraries( ${target} ${QT_LIBRARIES})

message ("QT library : ${QT_LIBRARIES}")
