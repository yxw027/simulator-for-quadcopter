TEMPLATE = lib
TARGET = Core
DEFINES += CORE_LIBRARY

include(../../simulatorplugin.pri)
include(coreplugin_dependencies.pri)
SOURCES += mainwindow.cpp \
    coreplugin.cpp \
    eventfilteringmainwindow.cpp
    
HEADERS += mainwindow.h \
    coreplugin.h \
    eventfilteringmainwindow.h
