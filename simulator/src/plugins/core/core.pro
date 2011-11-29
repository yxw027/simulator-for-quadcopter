TEMPLATE = lib
TARGET = Core
DEFINES += CORE_LIBRARY

include(../../simulatorplugin.pri)
include(coreplugin_dependencies.pri)
SOURCES += mainwindow.cpp \
    coreplugin.cpp \
    eventfilteringmainwindow.cpp
    
HEADERS += mainwindow.h \
    actionmanager/actioncontainer.h \
    actionmanager/actionmanager.h \
    actionmanager/command.h \
    actionmanager/actionmanager_p.h \
    actionmanager/command_p.h \
    actionmanager/actioncontainer_p.h \
    actionmanager/commandsfile.h \
    coreplugin.h \
    eventfilteringmainwindow.h
FORMS += dialogs/newdialog.ui \
    actionmanager/commandmappings.ui \
