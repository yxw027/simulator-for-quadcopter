#include <QDebug>

#include "SerialThread.h"
#include "qextserialport.h"

namespace Serial {

SerialThread::SerialThread(QextSerialPort *port, QObject *parent) : QThread(parent)
{
    this->port = port;
    
    stopped = false;
//    bool isOpen = this->port->open(QIODevice::ReadOnly);
//    if (isOpen) {
        // COMx is already in use
        //qDebug << port->deviceName() << "already in use";
//    }
/*    
    port->setBaudRate(BAUD9600);
    port->setDataBits(DATA_8);
    port->setParity(PAR_NONE);
    port->setStopBits(STOP_1);
    port->setFlowControl(FLOW_OFF);
*/    
    //qDebug() << port->deviceName() << "Connected";
}

SerialThread::~SerialThread()
{
    //qDebug() << port->deviceName() << "Disconnected";
}

void SerialThread::run()
{
    do {
        // Read data from COMx
    } while (!stopped);
    
    stopped = false;
}

void SerialThread::stopThread()
{
    mutex.lock();
    stopped = true;
    mutex.unlock();
}

void SerialThread::readData()
{
    // Check the buffer
    if (port->bytesAvailable() == 6)
    QByteArray temp = port->readAll();
    //qDebug() << "read:" << temp;
    //emit sensorDataReady;
}

} // namespace Serial