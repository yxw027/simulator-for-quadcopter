TEMPLATE = lib
TARGET = ExtKalmanFilter

DEFINES += EKF_LIBRARY
include(../../simulatorlibrary.pri)

HEADERS += \
    ktypes.hpp \
    kvector.hpp \
    kvector_impl.hpp \    
    kmatrix.hpp \
    kmatrix_impl.hpp \    
    kfilter.hpp \
    kfilter_impl.hpp \    
    ekfilter.hpp \
    ekfilter_impl.hpp

win32:CONFIG(debug, debug|release):RC_FILE = qextserialportd_resource.rc
else RC_FILE = qextserialport_resource.rc