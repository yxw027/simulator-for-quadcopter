include(../prj.pri)

PROJECT_LIB_PATH = $$PROJECT_ROOT_PATH/libs

win32 {
    DLLDESTDIR = $$(PROJECT_BIN_PATH)
}

DESTDIR = $$PROJECT_LIB_PATH

TARGET = $$qtLibraryTarget($$TARGET)
LIBS += -L$$PROJECT_LIB_PATH

win32 {
    target.path = /bin
    target.files = $$DESTDIR/$${TARGET}.dll
} else {
    target.path = /lib
}
INSTALLS += target

