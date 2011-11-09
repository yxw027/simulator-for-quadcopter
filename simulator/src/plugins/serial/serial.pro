TEMPLATE = lib
TARGET = Serial
include(../../qtcreatorplugin.pri)
DESTDIR = $$SIMULATOR_PLUGIN_PATH

HEADERS += serial.h
SOURCES += serial.cpp
OTHER_FILES += serial.pluginspec