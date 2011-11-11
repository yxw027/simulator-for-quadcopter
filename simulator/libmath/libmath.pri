# include and depend path
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

TEMPLATE += fakelib
MATH_LIB_NAME = $$qtLibraryTarget(math)
TEMPLATE -= fakelib

include($$PWD/../common.pri)

!math-buildlib {
    LIBS += -L$$PROJECT_LIB_DIR -l$$MATH_LIB_NAME
}else{
    HEADERS += $$PWD/qmath_global.h \
               $$PWD/qmath.h        \
               $$PWD/qcomplex.h

    SOURCES += $$PWD/qcomplex.cpp
}
