include(../libs/libs.pri)
TEMPLATE = app
TARGET = simulator-for-quadcopter

INCLUDEPATH += ../libs/QextSerialPort
DEPENDPATH += ../libs/QextSerialPort
QMAKE_LIBDIR += ../libs/QextSerialPort

HEADERS += \
    glwidget.h \
    window.h \
    SerialThread.h \

 QT +=  opengl

SOURCES += \
    glwidget.cpp \
    window.cpp \
    main.cpp \
    serialthread.cpp \



unix:DEFINES   = _TTY_POSIX_
win32:DEFINES  = _TTY_WIN_

OTHER_FILES += readme.txt

CONFIG(debug, debug|release):LIBS  += -lqextserialportd
else:LIBS  += -lqextserialport
