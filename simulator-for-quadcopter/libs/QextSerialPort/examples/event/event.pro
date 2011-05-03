######################################################################
# Enumerator
######################################################################


PROJECT = event
TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += ../..
QMAKE_LIBDIR += ../../build


OBJECTS_DIR    = obj
MOC_DIR        = moc
UI_DIR         = uic
CONFIG      += qt thread warn_on console


SOURCES += main.cpp \
			PortListener.cpp \
    ../../win_qextserialport.cpp \
    ../../qextserialport.cpp \
    ../../qextserialenumerator.cpp \
    ../../qextserialbase.cpp \
    ../../posix_qextserialport.cpp

HEADERS += PortListener.h \
    ../../win_qextserialport.h \
    ../../qextserialport.h \
    ../../qextserialenumerator.h \
    ../../qextserialbase.h \
    ../../posix_qextserialport.h


CONFIG(debug, debug|release):LIBS  += -lqextserialportd
else:LIBS  += -lqextserialport


win32:DEFINES  = _TTY_WIN_
