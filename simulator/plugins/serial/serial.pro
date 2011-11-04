TEMPLATE = lib

include($$PWD/../../common.pri)

CONFIG += plugin

TARGET = $$qtLibraryTarget(serial)

INCLUDEPATH += $$PWD/../

SOURCES = serial.cpp

DESTDIR = $$PROJECT_PLUGIN_DIR
