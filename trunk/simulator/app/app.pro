TEMPLATE = app
TARGET = simulator-for-quadcopter

CONFIG += qt
CONFIG += warn_on
CONFIG += silent

include(../libmath/libmath.pri)

DESTDIR = $$PROJECT_BIN_DIR

unix:QMAKE_RPATHDIR += $$PROJECT_LIB_DIR

HEADERS += \
    glwidget.h \
    mainwindow.h
    
SOURCES += \
    glwidget.cpp \
    mainwindow.cpp \
    main.cpp

# OpenGL support
QT +=   opengl
