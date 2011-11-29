include(../../simulator.pri)
include(../shared/qtsingleapplication/qtsingleapplication.pri)
TEMPLATE = app
TARGET = $$SIMULATOR_APP_TARGET
DESTDIR = $$SIMULATOR_APP_PATH

SOURCES += main.cpp

LIBS *= -l$$qtLibraryName(ExtensionSystem) -l$$qtLibraryName(qextserialport)

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
