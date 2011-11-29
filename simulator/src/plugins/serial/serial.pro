TEMPLATE = lib
TARGET = Serial
include(../../simulatorplugin.pri)
include(serial_dependencies.pri)

HEADERS += serialplugin.h \
           serialthread.h \
           serial.h

SOURCES += serialplugin.cpp \
           serialthread.cpp \
           serial.cpp
           
#RESOURCES += serial.qrc
