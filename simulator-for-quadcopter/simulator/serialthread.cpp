#include "SerialThread.h"
#include "qextserialport.h"

SerialThread::SerialThread(QextSerialPort *port, QObject *parent) : QThread(parent)
{
    this->port = port;
}

SerialThread::~SerialThread()
{

}

void SerialThread::run()
{
    // Read data from COM1
}

void SerialThread::readData()
{
    // Check the buffer
    if (port->bytesAvailable() == 6)
    QByteArray temp = port->readAll();
    //qDebug() << "read:" << temp;
}
