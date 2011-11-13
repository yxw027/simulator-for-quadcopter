#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>

QT_BEGIN_NAMESPACE
class QwtSamplingThread;
class QObject;
class QextSerialPort;
class QMutex;
QT_END_NAMESPACE

namespace Serial {

class SerialThread : public QThread
{
    Q_OBJECT

public:
    SerialThread(QextSerialPort *port, QObject *parent = 0);
    virtual ~SerialThread();
    
    void stopThread();
    
public slots:
    void readData();
    
protected:
    void run();

private:
    QextSerialPort *port;
    QMutex mutex;
    volatile bool stopped;
};

} // namespace Serial

#endif // SERIALTHREAD_H
