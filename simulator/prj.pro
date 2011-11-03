include(prj_common.pri)

TEMPLATE = subdirs
CONFIG  += ordered

qwt-uselib:SUBDIRS =    3rdparty    \
                        modules     \

SUBDIRS = simulator
