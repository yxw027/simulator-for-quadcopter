#include <QtGui>

#include "serial.h"

namespace Serial {

Serial::Serial()
{
}

Serial::~Serial()
{
}

bool Serial::open(const QString &portName)
{
    serialPort = new QextSerialPort(portName, QextSerialPort::EventDriven);
    
    bool isOpen = this->serialPort->open(QIODevice::ReadOnly);
    if (isOpen)
        return isOpen;

    // serial settings
    serialPort->setBaudRate(BAUD9600);
    serialPort->setFlowControl(FLOW_OFF);
    serialPort->setParity(PAR_NONE);
    serialPort->setDataBits(DATA_8);
    serialPort->setStopBits(STOP_1);
    // No effect if EventDriven
    // port->setTimeout(300);
    if (!(serialPort->lineStatus() & LS_DSR))
        QMessageBox::information(this, tr("Warning"), QString("%1 is not turned on").arg(portName));
    else
        qDebug() << serialPort->portName() << "Connected";
}

QString Serial::deviceName()
{
    Q_UNUSED(message)

    return serialPort->portName();
}

} // namespace Serial