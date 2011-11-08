include(../simulator.pri)

win32 {
    DLLDESTDIR = $$SIMULATOR_APP_PATH
}

DESTDIR = $$SIMULATOR_LIBRARY_PATH

TARGET = $$qtLibraryName($$TARGET)

!macx {
    win32 {
        target.path = /bin
        target.files = $$DESTDIR/$${TARGET}.dll
    } else {
        target.path = /$$SIMULATOR_LIBRARY_BASENAME/simulator
    }
    INSTALLS += target
}
