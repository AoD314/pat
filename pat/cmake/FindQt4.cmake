
find_package(Qt4 4.7.0 COMPONENTS QtCore QtGui QtNetwork REQUIRED)

include(${QT_USE_FILE})

include_directories( ${QT_INCLUDE_DIR} )

set(CMAKE_INCLUDE_DIRS_CONFIGCMAKE "${CMAKE_INCLUDE_DIRS_CONFIGCMAKE} ${QT_INCLUDE_DIR}")

set(QT_LIBS ${QT_LIBRARIES})

macro(check_moc file)
    file(STRINGS "${file}" lists_OBJS REGEX ".*Q_OBJECT.*")
    string(STRIP "${lists_OBJS}" str_str)
    string(COMPARE EQUAL "Q_OBJECT" "${str_str}" MOC_FILE_OBJ)

    file(STRINGS "${file}" lists_OBJS REGEX "include.*Qt.*")
    string(STRIP "${lists_OBJS}" str_str)
    string(COMPARE NOTEQUAL "" "${str_str}" MOC_FILE_INC)

    set(MOC_FILE MOC_FILE_OBJ OR MOC_FILE_INC)
endmacro()

