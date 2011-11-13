#include <QObject>


#include "qextserialport/qextserialport.h"

namespace Serial {

class Serial : public QObject
{
    Q_OBJECT
    
public:
    Serial();
    virtual ~Serial();
    
    bool open(const QString &portName);
    QString deviceName();
    
private:
    QextSerialPort *serialPort;
    SerialThread serialthread;
    bool isOpen;
};

} // namespace Serial