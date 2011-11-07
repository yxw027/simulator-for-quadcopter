include(../../simulator.pri)
TEMPLATE = app
TARGET = $$SIMULATOR_APP_TARGET
DESTDIR = $$SIMULATOR_APP_PATH

LIBS *= -l$$qtLibraryName(ExtensionSystem) -l$$qtLibraryName(Aggregation)

unix:QMAKE_RPATHDIR += $$PROJECT_LIB_DIR
    
SOURCES += main.cpp

#OTHER_FILES += simulator.rc

# OpenGL support
QT +=   opengl
