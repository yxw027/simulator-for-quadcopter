TEMPLATE = lib
TARGET = Math

DEFINES += MATH_LIBRARY
include(../../simulatorlibrary.pri)

HEADERS += math_global.h \
           quat.h \
           euler.h

SOURCES += quat.cpp \
           euler.cpp