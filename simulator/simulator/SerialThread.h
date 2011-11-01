#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
class QwtSamplingThread;
class QObject;
class QextSerialPort;


class SerialThread : public QThread
{
    Q_OBJECT

public:
    SerialThread(QextSerialPort *port, QObject *parent = 0);
    virtual ~SerialThread();

public slots:
    void readData();

protected:
    void run();

private:
    QextSerialPort *port;
    bool stopped;
};

#endif // SERIALTHREAD_H
