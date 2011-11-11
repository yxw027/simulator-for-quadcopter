include(../qtcreator.pri)

isEmpty(USE_USER_DESTDIR) {
    DESTDIR = $$IDE_PLUGIN_PATH/$$PROVIDER
}
LIBS += -L$$DESTDIR

# copy the plugin spec
isEmpty(TARGET) {
    error("simulatorplugin.pri: You must provide a TARGET")
}
PLUGINSPEC = $$_PRO_FILE_PWD_/$${TARGET}.pluginspec
TARGET = $$qtLibraryName($$TARGET)
