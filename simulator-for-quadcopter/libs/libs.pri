include(../prj.pri)

PROJECT_LIB_PATH = $$PROJECT_ROOT_PATH/libs

win32 {
    DLLDESTDIR = $$(PROJECT_BIN_PATH)
}

DESTDIR = $$PROJECT_LIB_PATH

TARGET = $$qtLibraryTarget($$TARGET)

INCLUDEPATH += $$PROJECT_LIB_PATH/

DEPENDPATH += \
    $$PROJECT_LIB_PATH

LIBS += -L$$PROJECT_LIB_PATH \
        -L$$PROJECT_LIB_PATH/Qwt/lib

win32 {
    target.path = /bin
    target.files = $$DESTDIR/$${TARGET}.dll
} else {
    target.path = /lib
}
INSTALLS += target

