#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <qwt_sampling_thread.h>


class SerialThread : public QwtSamplingThread
{
    Q_OBJECT

public:
    SerialThread(QObject *parent = 0);
    virtual ~SerialThread();

public slots:
    void read();

private:
    QextSerialPort *port;
};

#endif // SERIALTHREAD_H
