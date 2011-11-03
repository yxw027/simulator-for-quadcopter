#
# project common environment varible
#
#PROJECT_ROOT_DIR = $$PWD
PROJECT_LIB_DIR = $$PWD/lib
PROJECT_BIN_DIR = $$PWD/bin

# library configuration
#infile(config.pri, SOLUTIONS_LIBRARY, yes): CONFIG += qwt-uselib
infile(config.pri, SOLUTIONS_LIBRARY, yes) {
    CONFIG += qwt-uselib
    CONFIG += qmath-uselib
}


TEMPLATE += fakelib
QWT_LIB_NAME = $$qtLibraryTarget(qwt)
QMATH_LIB_NAME = $$qtLibraryTarget(qmath)
TEMPLATE -= fakelib

#target directory
#win32 {
#    DLLDESTDIR = ....lib
#} else {
#    DESTDIR = 
#}