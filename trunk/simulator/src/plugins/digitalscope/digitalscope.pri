INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS = \
    curvedata.h \
    sensordata.h \
    serialsamplingthread.h \
    seriesdata.h \
    plot.h \
    serialdialog.h \
    mainwindow.h \
    glwidget.h

SOURCES = \
    curvedata.cpp \
    sensordata.cpp \
    serialsamplingthread.cpp \
    seriesdata.cpp \
    plot.cpp \
    serialdialog.cpp \
    mainwindow.cpp \
    glwidget.cpp

RESOURCES += digitalscope.qrc

include(../../libs/3rdparty/qextserialport/qextserialport.pri)
include(../../libs/3rdparty/qwt/qwt.pri)

# OpenGL support
QT += opengl
