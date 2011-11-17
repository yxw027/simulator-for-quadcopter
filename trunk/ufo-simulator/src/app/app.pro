include(../../simulator.pri)
TEMPLATE = app

TARGET = $$SIMULATOR_APP_TARGET
DESTDIR = $$SIMULATOR_APP_PATH

SOURCES += main.cpp

LIBS *= -l$$qtLibraryName(Math)

win32 {
    RC_FILE = simulator.rc
    target.path = /bin
    INSTALLS += target
} else {
    target.path  = /bin
    INSTALLS    += target
}    