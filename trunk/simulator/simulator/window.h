#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QSlider;
class QextSerialPort;
class QPushButton;
class GLWidget;
class QGroupBox;
class SerialThread;
class Plot;
class AbstractSerial;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    virtual ~Window();
    
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void readData();
    void sendData();
    void startOrStopSerialThread();
    
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QSlider *createSlider();
    QGroupBox *createAcclGroupBox();
    QGroupBox *createGyroGroupBox();
    QGroupBox *createImuGroupBox();

    GLWidget *glWidget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;

    QGroupBox *acclGroupBox;
    QGroupBox *gyroGroupBox;
    QGroupBox *imuGroupBox;

    QPushButton *pushButton;
    QPushButton *serialButton;
#if 1    
    QextSerialPort *port;
#else    
    AbstractSerial *port;
    
    SerialThread *serialThread;
    Plot *plot;
};

#endif // WINDOW_H
