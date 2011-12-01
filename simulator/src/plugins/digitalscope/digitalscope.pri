INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS = \
    curvedata.h \
    sensordata.h \
    serialsamplingthread.h \
    serialpacket.h \
    mainwindow.h \
    glwidget.h

SOURCES = \
    curvedata.cpp \
    sensordata.cpp \
    serialsamplingthread.cpp \
    serialpacket.cpp \
    mainwindow.cpp \
    glwidget.cpp

include(../../libs/3rdparty/qextserialport/qextserialport.pri)
include(../../libs/3rdparty/qwt/qwt.pri)
