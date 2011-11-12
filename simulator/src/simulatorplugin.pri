include(../simulator.pri)

isEmpty(PROVIDER) {
    PROVIDER = Nokia
}

isEmpty(USE_USER_DESTDIR) {
    DESTDIR = $$SIMULATOR_PLUGIN_PATH/$$PROVIDER
}
LIBS += -L$$DESTDIR

# copy the plugin spec
isEmpty(TARGET) {
    error("simulatorplugin.pri: You must provide a TARGET")
}

PLUGINSPEC = $$_PRO_FILE_PWD_/$${TARGET}.pluginspec

TARGET = $$qtLibraryName($$TARGET)
