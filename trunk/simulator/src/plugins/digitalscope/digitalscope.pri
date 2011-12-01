INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS = \
    curvedata.h \
    sensordata.h \
    serialsamplingthread.h \
    plot.h \
    mainwindow.h \
    glwidget.h

SOURCES = \
    curvedata.cpp \
    sensordata.cpp \
    serialsamplingthread.cpp \
    plot.cpp \
    mainwindow.cpp \
    glwidget.cpp

include(../../libs/3rdparty/qextserialport/qextserialport.pri)
include(../../libs/3rdparty/qwt/qwt.pri)

# OpenGL support
QT += opengl
