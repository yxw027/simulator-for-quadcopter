#inclue <QObject>

#include "../serialplugin.h"

class Serial : public Object, SerialPlugin {
    Q_OBJECT
    Q_INTERFACE(SerialPlugin)
    
public:
    QString deviceName();    
};

Serial::~Serial()
{
}

QString Serial::deviceName()
{
    return new QString("COM1");
    //return mSerialPort->portName();
}

Q_EXPORT_PLUGIN2(serial, Serial)
