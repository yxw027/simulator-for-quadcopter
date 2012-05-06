     #include "serialsamplingthread.h"
#include "sensordata.h"

#include <qextserialport.h>
#include <qextserialenumerator.h>

#include <qwt_math.h>
#include <math.h>

#include <QList>
#include <QDebug>


SerialSamplingThread::SerialSamplingThread(QObject *parent/*, QString &portName*/) :
    QwtSamplingThread(parent), m_frequency(0.01), m_amplitude(5.0*2.0)
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
#ifdQ_OS_WIN
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

double SerialSamplingThread::frequency() const
{
    return m_frequency;
}

double SerialSamplingThread::amplitude() const
{
    return m_amplitude;
}

void SerialSamplingThread::setFrequency(double frequency)
{
    m_frequency = frequency;
}

void SerialSamplingThread::setAmplitude(double amplitude)
{
    m_amplitude = amplitude;
}

QList<QextPortInfo> SerialSamplingThread::availableports()
{
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();

    return ports;
}

void SerialSamplingThread::read()
{
    // Check the buffer
    if (port->bytesAvailable() > 0) {
        QByteArray temp = port->readAll();
        //qDebug() << "read:" << temp;
        //emit sensorDataReady;
    }
}

bool SerialSamplingThread::connect(QString portName)
{
}

void SerialSamplingThread::disconnect()
{
}

void SerialSamplingThread::sample(double elapsed)
{
//  qDebug() << elapsed;
    if (m_frequency > 0.0) {
        const double period = 1.0 / m_frequency;
        const double x = ::fmod(elapsed, period);
        const double y = 2.0 * qFastSin(x / period * 2 *M_PI);
        const QPointF point(elapsed, y);
        SensorData::instance().append(point);
    }
}
