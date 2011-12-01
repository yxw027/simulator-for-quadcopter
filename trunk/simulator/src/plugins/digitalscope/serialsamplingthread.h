#ifndef SERIALSAMPLINGTHREAD_H
#define SERIALSAMPLINGTHREAD_H

#include <qwt_sampling_thread.h>

QT_BEGIN_NAMESPACE
class QextSerialPort;
QT_END_NAMESPACE

class SerialSamplingThread : public QwtSamplingThread
{
    Q_OBJECT

public:
    SerialSamplingThread(QObject *parent = 0/*, QString &portName*/);
    virtual ~SerialSamplingThread();

public slots:
    void read();

protected:
    virtual void sample(double elapsed);

private:
    QextSerialPort *port;
    bool m_isOpen;
};

#endif // SERIALSAMPLINGTHREAD_H
