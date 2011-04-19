INCLUDEPATH += E:\prj\quadcopter\simulator\qextserialport-1.2win-alpha\


HEADERS += \
    window.h \
    glwidget.h \
    imufilter.h \
    qextserialport-1.2win-alpha/win_qextserialport.h \
    qextserialport-1.2win-alpha/qextserialport.h \
    qextserialport-1.2win-alpha/qextserialbase.h \
    imu.h

SOURCES += \
    window.cpp \
    main.cpp \
    glwidget.cpp \
    imufilter.cpp \
    qextserialport-1.2win-alpha/qextserialport.cpp \
    qextserialport-1.2win-alpha/qextserialbase.cpp \
    qextserialport-1.2win-alpha/win_qextserialport.cpp \
    imu.cpp

QT  += opengl
