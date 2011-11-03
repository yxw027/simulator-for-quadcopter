include($$PWD/../../prj_common.pri)

# include and depend path
INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src

qmath-uselib:!qmath-buildlib {
    LIBS += -L$$PROJECT_LIB_DIR -l$$QMATH_LIB_NAME
} else {
    HEADERS += $$PWD/src/qmath_global.h \
               $$PWD/src/qmath.h        \
               $$PWD/src/qcomplex.h

    SOURCES += $$PWD/src/qcomplex.cpp
}

win32 {
    contains(TEMPLATE, lib):contains(CONFIG, shared):DEFINES += QMATH_DLL
    else:qtcolorpicker-uselib:DEFINES += QT_MATH_IMPORT 
}
    
# qmake internal option
CONFIG += qt
CONFIG += warn_on
CONFIG += silent
CONFIG += no_keywords

# debug and release mode
win32 {
    CONFIG += debug_and_release 
    CONFIG += build_all
}

# moc obj res
MOC_DIR = moc
OBJ_DIR = obj
RCC_DIR = resource