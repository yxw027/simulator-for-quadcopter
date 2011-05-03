include(../libs/libs.pri)
TEMPLATE = app
TARGET = simulator-for-quadcopter

INCLUDEPATH += $$PROJECT_LIB_PATH/QextSerialPort

HEADERS += \
    glwidget.h \
    window.h \
    SerialThread.h \

SOURCES += \
    glwidget.cpp \
    window.cpp \
    main.cpp \
    serialthread.cpp \

QT +=  opengl

unix:DEFINES   = _TTY_POSIX_
win32:DEFINES  = _TTY_WIN_

OTHER_FILES += README

CONFIG(debug, debug|release):LIBS  += -lqextserialportd
else:LIBS  += -lqextserialport
