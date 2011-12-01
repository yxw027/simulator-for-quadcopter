#include "serialsamplingthread.h"

#include <qextserialport.h>
#include <qextserialenumerator.h>
#include <QList>
#include <QDebug>


SerialSamplingThread::SerialSamplingThread(QObject *parent/*, QString &portName*/) :
    QwtSamplingThread(parent)
{/*
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    foreach(QextPortInfo portInfo, ports) {
        if(portInfo.friendName == portName) {
            PortSettings settings;
            settings.BaudRate = BAUD115200;
            settings.DataBits = DATA_8;
            settings.Parity = PAR_NONE;
            settings.StopBits = STOP_1;
            settings.FlowControl = FLOW_OFF;
        #ifdef Q_OS_WIN
            port = new QextSerialPort(portInfo.portName, &settings, QextSerialPort::EventDriven);
        #else
            port = new QextSerialPort(portInfo.physName, &settings, QextSerialPort::EventDriven);
        #endif
        }
    }
    m_isOpen = port->isOpen();
    if (m_isOpen)
        qDebug() << port->portName() << "Connected";
    else
        qDebug() << "Error:" << port->portName() << port->errorString();*/
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
