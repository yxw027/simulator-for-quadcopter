include(../simulator.pri)

DESTDIR = $$SIMULATOR_LIBRARY_PATH

TARGET = $$qtLibraryName($$TARGET)

win32 {
    DLLDESTDIR = $$SIMULATOR_APP_PATH
}

!macx {
    win32 {
        target.path = /bin
        target.files = $$DESTDIR/$${TARGET}.dll
    } else {
        target.path = /$$SIMULATOR_LIBRARY_BASENAME/simulator
    }
    INSTALLS += target
}
