
TEMPLATE = lib
CONFIG  += qt warn_on release

HEADERS += lib/include/pat/pat.hpp \
           lib/include/pat/pat_base.hpp \
           lib/include/pat/pat_convert.hpp \
           lib/include/pat/pat_params.hpp \
           lib/include/pat/pat_record_params.hpp \
           lib/include/pat/pat_system.hpp \
           lib/include/pat/pat_strparam.hpp \
           lib/include/pat/version.hpp \
           lib/include/pat/algorithm.hpp \
           lib/include/pat/alg_bruteforce.hpp \
           lib/include/pat/alg_gradient.hpp \


SOURCES += lib/src/pat_base.cpp \
           lib/src/pat_convert.cpp \
           lib/src/pat_params.cpp \
           lib/src/alg_bruteforce.cpp \
           lib/src/alg_gradient.cpp \
           lib/src/algorithm.cpp \
           lib/src/pat_strparam.cpp \
           lib/src/pat_system.cpp \

INCLUDEPATH = lib/include 
win32:DEFINES += QT_DLL


