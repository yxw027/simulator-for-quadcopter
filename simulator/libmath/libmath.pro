TEMPLATE = lib
CONFIG += math-buildlib

include($$PWD/libmath.pri)

TARGET  = $$MATH_LIB_NAME


#CONFIG += shared


DEFINES += QMATH_DLL

# debug and release mode
win32 {
    CONFIG += debug_and_release 
    CONFIG += build_all
}

DESTDIR = $$PROJECT_LIB_DIR
win32 {
    DLLDESTDIR = $$PROJECT_BIN_DIR
    QMAKE_DISTCLEAN += $$PROJECT_BIN_DIR/$${MATH_LIB_NAME}.dll
}
#include($$PWD/../mysharedlib_config.pri)
#include($$PWD/../mysharedlib.pri)