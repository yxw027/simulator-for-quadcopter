#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

class QObject;
#include <QThread>
class QextSerialPort;

class SerialThread : public QThread
{
    Q_OBJECT

public:
    SerialThread(QextSerialPort *port, QObject *parent = 0);
    virtual ~SerialThread();

public slots:
    void read();

protected:
    void run();

private:
    QextSerialPort *port;
};

#endif // SERIALTHREAD_H
