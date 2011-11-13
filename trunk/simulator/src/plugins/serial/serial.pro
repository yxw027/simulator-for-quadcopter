TEMPLATE = lib
TARGET = Serial
DEFINES += SERIAL_LIBRARY
include(../../simulatorplugin.pri)
include(serial_dependencies.pri)

HEADERS += serialplugin.h \
           serialthread.h 

SOURCES += serialplugin.cpp \
           serialthread.cpp

#RESOURCES += serial.qrc
