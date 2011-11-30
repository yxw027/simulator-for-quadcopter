INCLUDEPATH += \
    $$PWD \
    $$PWD/../../libs/3rdparty/qwt/src

DEPENDPATH += $$PWD

HEADERS = \
    curvedata.h \
    sensordata.h \
#    serialplugin.h \
    serialsamplingthread.h \
    serialpacket.h \
    mainwindow.h

SOURCES = \
    curvedata.cpp \
    sensordata.cpp \
#    serialplugin.cpp \
    serialsamplingthread.cpp \
    serialpacket.cpp \
    mainwindow.cpp

include(../../libs/3rdparty/qextserialport/qextserialport.pri)
#include(../../libs/3rdparty/qwt/qwt.pri)
