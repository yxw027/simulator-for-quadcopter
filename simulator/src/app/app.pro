include(../../simulator.pri)
#include(../libs/3rdparty/qextserialport/qextserialport.pri)
#include(../plugins/digitalscope/digitalscope.pri)

TEMPLATE = app
TARGET = $$SIMULATOR_APP_TARGET
DESTDIR = $$SIMULATOR_APP_PATH

SOURCES += main.cpp

win32 {
    RC_FILE = simulator.rc
    target.path = /bin
    INSTALLS += target
} else {
    target.path  = /bin
    INSTALLS    += target
}
# OpenGL support
#QT +=   opengl
