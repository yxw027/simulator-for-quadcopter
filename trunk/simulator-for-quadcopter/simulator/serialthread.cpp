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

void SerialThread::read()
{
    QByteArray temp = port->readAll();
    //qDebug() << "read:" << temp;
}
