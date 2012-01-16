TEMPLATE  = subdirs
CONFIG   += ordered
QT += core gui

# aggregation and extensionsystem are directly in src.pro
# because of dependencies of app
SUBDIRS   = \
    3rdparty \
    kalman
