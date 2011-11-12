include(../../simulator.pri)
include(../shared/qtsingleapplication/qtsingleapplication.pri)
TEMPLATE = app
TARGET = $$SIMULATOR_APP_TARGET
DESTDIR = $$SIMULATOR_APP_PATH

SOURCES += main.cpp

include(../rpath.pri)
LIBS *= -l$$qtLibraryName(ExtensionSystem) -l$$qtLibraryName(Aggregation)



#OTHER_FILES += simulator.rc

# OpenGL support
#QT +=   opengl
