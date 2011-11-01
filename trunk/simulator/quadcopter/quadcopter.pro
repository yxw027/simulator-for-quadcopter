TEMPLATE = app
TARGET = simulator-for-quadcopter

#INCLUDEPATH += ../3rdparty/QextSerialPort/include \
#               ../3rdparty/Qwt/include
#DEPENDPATH += \
#    ../3rdparty/QextSerialPort/include \
#    ../3rdparty/Qwt/include
#DESTDIR = $$PROJECT_BIN_PATH

HEADERS += \
    glwidget.h \
    window.h \
    SerialThread.h \
    scope/plot.h \
    scope/sensordata.h \
    scope/curvedata.h

SOURCES += \
    glwidget.cpp \
    window.cpp \
    main.cpp \
    serialthread.cpp \
    scope/plot.cpp \
    scope/sensordata.cpp \
    scope/curvedata.cpp

QT +=  opengl

unix:DEFINES   = _TTY_POSIX_
win32:DEFINES  = _TTY_WIN_

OTHER_FILES += README

CONFIG(debug, debug|release) {
    LIBS  += -L$$PWD/../3rdparty/QextSerialPort/lib \
             -L$$PWD/../3rdparty/Qwt/lib
    qtAddLibrary(qextserialport)
    qtAddLibrary(qwt)
}
else:LIBS  += -lqextserialport \
              -lqwt
