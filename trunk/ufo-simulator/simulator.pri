SIMULATOR_VERSION = 0.0.1

defineReplace(cleanPath) {
    win32:1 ~= s|\\\\|/|g
    contains(1, ^/.*):pfx = /
    else:pfx =
    segs = $$split(1, /)
    out =
    for(seg, segs) {
        equals(seg, ..):out = $$member(out, 0, -2)
        else:!equals(seg, .):out += $$seg
    }
    return($$join(out, /, $$pfx))
}

defineReplace(targetPath) {
    return($$replace(1, /, $$QMAKE_DIR_SEP))
}

defineReplace(qtLibraryName) {
   unset(LIBRARY_NAME)
   LIBRARY_NAME = $$1
   CONFIG(debug, debug|release) {
      !debug_and_release|build_pass {
          mac:RET = $$member(LIBRARY_NAME, 0)_debug
              else:win32:RET = $$member(LIBRARY_NAME, 0)d
      }
   }
   isEmpty(RET):RET = $$LIBRARY_NAME
   return($$RET)
}
isEmpty(SIMULATOR_LIBRARY_BASENAME) {
    SIMULATOR_LIBRARY_BASENAME = lib
}

SIMULATOR_SOURCE_TREE = $$PWD
isEmpty(SIMULATOR_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    SIMULATOR_BUILD_TREE = $$cleanPath($$OUT_PWD)
    SIMULATOR_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}
SIMULATOR_APP_PATH = $$SIMULATOR_BUILD_TREE/bin
macx {
} else {
    contains(TEMPLATE, vc.*):vcproj = 1
    SIMULATOR_APP_TARGET   = simulator
    SIMULATOR_LIBRARY_PATH = $$SIMULATOR_BUILD_TREE/$$SIMULATOR_LIBRARY_BASENAME/simulator
    SIMULATOR_PLUGIN_PATH  = $$SIMULATOR_LIBRARY_PATH/plugins
    SIMULATOR_DATA_PATH    = $$SIMULATOR_BUILD_TREE/share/simulator
    SIMULATOR_DOC_PATH     = $$SIMULATOR_BUILD_TREE/share/doc/simulator
    SIMULATOR_APP_PATH     = $$SIMULATOR_APP_PATH
}

INCLUDEPATH += \
    $$SIMULATOR_BUILD_TREE/src \
    $$SIMULATOR_SOURCE_TREE/src/libs \
    $$IDE_SOURCE_TREE/src/plugins

CONFIG += depend_includepath
CONFIG += warn_on
CONFIG += silent

LIBS += -L$$SIMULATOR_LIBRARY_PATH

!isEmpty(vcproj) {
    DEFINES += SIMULATOR_LIBRARY_BASENAME=\"$$SIMULATOR_LIBRARY_BASENAME\"
} else {
    DEFINES += SIMULATOR_LIBRARY_BASENAME=\\\"$$SIMULATOR_LIBRARY_BASENAME\\\"
}

DEFINES += QT_NO_CAST_TO_ASCII
!macx:DEFINES += QT_USE_FAST_OPERATOR_PLUS QT_USE_FAST_CONCATENATION
