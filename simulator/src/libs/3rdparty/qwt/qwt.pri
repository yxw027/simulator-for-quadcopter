################################################################
# Qwt Widget Library
# Copyright (C) 1997   Josef Wilgen
# Copyright (C) 2002   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
###################################################################

QWT_ROOT = $$PWD
include( $${QWT_ROOT}/qwtconfig.pri )

INCLUDEPATH += $${QWT_ROOT}/src
DEPENDPATH  += $${QWT_ROOT}/src

LIBS *= -l$$qtLibraryName(Qwt)

contains(QWT_CONFIG, QwtSvg) {

    QT += svg
}
else {

    DEFINES += QWT_NO_SVG
}

win32 {
    contains(QWT_CONFIG, QwtDll) {
        DEFINES += QT_DLL QWT_DLL
    }
}
