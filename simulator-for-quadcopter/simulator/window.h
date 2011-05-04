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

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void readData();
    void sendData();

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

    QextSerialPort *port;
    SerialThread *thread;
    Plot *plot;
};

#endif // WINDOW_H
