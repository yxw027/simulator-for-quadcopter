TEMPLATE = app
TARGET = simulator-for-quadcopter

include(../libmath/libmath.pri)

DESTDIR = $$PROJECT_BIN_DIR

unix:QMAKE_RPATHDIR += $$PROJECT_LIB_DIR

HEADERS += \
    mainwindow.h
    
SOURCES += \
    mainwindow.cpp \
    main.cpp
