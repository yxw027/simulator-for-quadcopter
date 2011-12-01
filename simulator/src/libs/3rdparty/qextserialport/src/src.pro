PROJECT = qextserialport
TEMPLATE = lib
TARGET = QextSerialPort
CONFIG += qt
CONFIG += dll

# event driven device enumeration on windows requires the gui module
!win32:QT -= gui

DEFINES += QEXTSERIALPORT_LIB
include(../../../../simulatorlibrary.pri)

HEADERS = \
    qextserialport.h \
    qextserialenumerator.h \
    qextserialport_global.h

SOURCES = qextserialport.cpp

unix:SOURCES += posix_qextserialport.cpp
unix:!macx:SOURCES += qextserialenumerator_unix.cpp
macx {
    SOURCES += qextserialenumerator_osx.cpp
    LIBS += -framework IOKit -framework CoreFoundation
}

win32 {
    SOURCES += win_qextserialport.cpp qextserialenumerator_win.cpp
    DEFINES += WINVER=0x0501 # needed for mingw to pull in appropriate dbt business...probably a better way to do this
    LIBS += -lsetupapi
}

win32::CONFIG(release, debug|release): RC_FILE = qextserialport_resource.rc
else win32:CONFIG(debug, debug|release): RC_FILE = qextserialportd_resource.rc
