#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <qwt_sampling_thread.h>

QT_BEGIN_NAMESPACE
class QextSerialPort;
QT_END_NAMESPACE

class SerialSamplingThread : public QwtSamplingThread
{
    Q_OBJECT

public:
    SerialSamplingThread(QObject *parent = 0);
    virtual ~SerialSamplingThread();

public slots:
    void read();

protected:
    virtual void sample(double elapsed);

private:
    QextSerialPort *port;
};

#endif // SERIALTHREAD_H
