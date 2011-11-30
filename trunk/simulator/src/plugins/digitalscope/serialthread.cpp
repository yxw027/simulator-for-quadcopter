#include "SerialThread.h"

SerialThread::SerialThread(/*QextSerialPort *port, */QObject *parent) : QThread(parent)
{
    this->port = port;
/*    
    port->setBaudRate(BAUD9600);
    port->setDataBits(DATA_8);
    port->setParity(PAR_NONE);
    port->setStopBits(STOP_1);
    port->setFlowControl(FLOW_OFF);
*/    
    qDebug() << port->portName() << "Connected";
}

SerialThread::~SerialThread()
{
    qDebug() << port->portName() << "Disconnected";
}

void SerialThread::read()
{
    // Check the buffer
    if (port->bytesAvailable() == 6)
    QByteArray temp = port->readAll();
    //qDebug() << "read:" << temp;
    //emit sensorDataReady;
}
