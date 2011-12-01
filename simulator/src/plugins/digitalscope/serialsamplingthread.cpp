#include "serialsamplingthread.h"
#include "qextserialport.h"

#include <QDebug>


SerialSamplingThread::SerialSamplingThread(/*QextSerialPort *port, */QObject *parent)
{
/*    this->port = port;
    
    port->setBaudRate(BAUD9600);
    port->setDataBits(DATA_8);
    port->setParity(PAR_NONE);
    port->setStopBits(STOP_1);
    port->setFlowControl(FLOW_OFF);
   
    qDebug() << port->portName() << "Connected";*/ 
}

SerialSamplingThread::~SerialSamplingThread()
{
    qDebug() << port->portName() << "Disconnected";
}

void SerialSamplingThread::read()
{
    // Check the buffer
    if (port->bytesAvailable() == 6)
    QByteArray temp = port->readAll();
    //qDebug() << "read:" << temp;
    //emit sensorDataReady;
}

void SerialSamplingThread::sample(double elapsed)
{
}
