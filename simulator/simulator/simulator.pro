TEMPLATE = app
TARGET = app

#PROJECT_BIN_PATH = bin

#INCLUDEPATH += ../3rdparty/qextserialport/include \
#               ../3rdparty/qwt/include
#DEPENDPATH += \
#    ../3rdparty/QextSerialPort/include \
#    ../3rdparty/Qwt/include
#DESTDIR = $$PROJECT_BIN_PATH


#include(../3rdparty/qwt/examples/examples.pri)
include(scope/scope.pri)
include($$PWD/../../3rdparty/modules/qmath/qmath.pri)
#include(simulator.pri)

HEADERS += \
    glwidget.h \
    window.h \
    SerialThread.h

SOURCES += \
    glwidget.cpp \
    window.cpp \
    main.cpp \
    serialthread.cpp

QT +=  opengl

unix:DEFINES   = _TTY_POSIX_
win32:DEFINES  = _TTY_WIN_

OTHER_FILES += README

#qtAddLibrary(qextserialport)
#qtAddLibrary(qwt)
#qtAddLibrary(qextmath)

#CONFIG(debug, debug|release) {
#    LIBS  += -L$$PWD/../3rdparty/QextSerialPort/lib \
#             -L$$PWD/../3rdparty/Qwt/lib
#    qtAddLibrary(qextserialport)
#    qtAddLibrary(qwt)
#}
#else:LIBS  += -lqextserialport \
#              -lqwt
