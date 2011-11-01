#include <QtGui>
#include <QDebug>
#include "qextserialport.h"

#include "glwidget.h"
#include "window.h"
#include "SerialThread.h"
#include "./scope/plot.h"

Window::Window()
{

    glWidget = new GLWidget;

    xSlider = createSlider();
    ySlider = createSlider();
    zSlider = createSlider();

    pushButton = new QPushButton(tr("pushButton"));
    plot = new Plot(this);

    connect(xSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setXRotation(int)));
    connect(glWidget, SIGNAL(xRotationChanged(int)), xSlider, SLOT(setValue(int)));
    connect(ySlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setYRotation(int)));
    connect(glWidget, SIGNAL(yRotationChanged(int)), ySlider, SLOT(setValue(int)));
    connect(zSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZRotation(int)));
    connect(glWidget, SIGNAL(zRotationChanged(int)), zSlider, SLOT(setValue(int)));

    port = new QextSerialPort("COM1", QextSerialPort::EventDriven);
    port->open(QIODevice::ReadWrite);
    port->setBaudRate(BAUD9600);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_2);
    port->setTimeout(300);
    if (!(port->lineStatus() & LS_DSR))
        qDebug() << "warning: device is not turned on";

    SerialThread *thread = new SerialThread(port);
    connect(port, SIGNAL(readyRead()), thread, SLOT(readData()));
    thread->start();

    //connect(port, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(pushButton, SIGNAL(clicked()), this, SLOT(sendData()));

    acclGroupBox = createAcclGroupBox();
    gyroGroupBox = createGyroGroupBox();
    imuGroupBox = createImuGroupBox();

    QHBoxLayout *sensorDataLayout = new QHBoxLayout;
    sensorDataLayout->addWidget(acclGroupBox);
    sensorDataLayout->addWidget(gyroGroupBox);
    sensorDataLayout->addWidget(imuGroupBox);

    QVBoxLayout *sensorLayout = new QVBoxLayout;
    sensorLayout->addWidget(plot);
    //sensorLayout->addLayout(sensorDataLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(glWidget);
    mainLayout->addWidget(xSlider);
    mainLayout->addWidget(ySlider);
    mainLayout->addWidget(zSlider);
    mainLayout->addLayout(sensorLayout);
    setLayout(mainLayout);

    xSlider->setValue(15 * 16);
    ySlider->setValue(345 * 16);
    zSlider->setValue(0 * 16);
    setWindowTitle(tr("simulator"));

}

QSize Window::minimumSizeHint() const
{
    return QSize(200, 200);
}

QSize Window::sizeHint() const
{
    return QSize(600, 200);
}

QSlider *Window::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

QGroupBox *Window::createAcclGroupBox()
{
    acclGroupBox = new QGroupBox(tr("Accelerometer"));

    QHBoxLayout *xAccelHBox = new QHBoxLayout;
    QLabel *xAccel = new QLabel(tr("X"));
    QLCDNumber *xAccelLcd = new QLCDNumber(this);
    xAccelLcd->adjustSize();
    xAccelHBox->addWidget(xAccel);
    xAccelHBox->addWidget(xAccelLcd);

    QHBoxLayout *yAccelHBox = new QHBoxLayout;
    QLabel *yAccel = new QLabel(tr("Y"));
    QLCDNumber *yAccelLcd = new QLCDNumber(this);
    yAccelHBox->addWidget(yAccel);
    yAccelHBox->addWidget(yAccelLcd);

    QHBoxLayout *zAccelHBox = new QHBoxLayout;
    QLabel *zAccel = new QLabel(tr("Z"));
    QLCDNumber *zAccelLcd = new QLCDNumber(this);
    zAccelHBox->addWidget(zAccel);
    zAccelHBox->addWidget(zAccelLcd);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addLayout(xAccelHBox);
    vbox->addLayout(yAccelHBox);
    vbox->addLayout(zAccelHBox);
    vbox->addStretch(1);
    acclGroupBox->setLayout(vbox);

    return acclGroupBox;
}

QGroupBox *Window::createGyroGroupBox()
{
    gyroGroupBox = new QGroupBox(tr("Gyroscope"));

    QHBoxLayout *xGyroHBox = new QHBoxLayout;
    QLabel *xGyro = new QLabel(tr("X"));
    QLCDNumber *xGyroLcd = new QLCDNumber(this);
    xGyroHBox->addWidget(xGyro);
    xGyroHBox->addWidget(xGyroLcd);

    QHBoxLayout *yGyroHBox = new QHBoxLayout;
    QLabel *yGyro = new QLabel(tr("Y"));
    QLCDNumber *yGyroLcd = new QLCDNumber(this);
    yGyroHBox->addWidget(yGyro);
    yGyroHBox->addWidget(yGyroLcd);

    QHBoxLayout *zGyroHBox = new QHBoxLayout;
    QLabel *zGyro = new QLabel(tr("Z"));
    QLCDNumber *zGyroLcd = new QLCDNumber(this);
    zGyroHBox->addWidget(zGyro);
    zGyroHBox->addWidget(zGyroLcd);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addLayout(xGyroHBox);
    vbox->addLayout(yGyroHBox);
    vbox->addLayout(zGyroHBox);
    vbox->addStretch(1);
    gyroGroupBox->setLayout(vbox);

    return gyroGroupBox;
}

QGroupBox *Window::createImuGroupBox()
{
    imuGroupBox = new QGroupBox(tr("IMU parameter"));

    QHBoxLayout *xImuHBox = new QHBoxLayout;
    QLabel *xImu = new QLabel(tr("Pitch"));
    QLCDNumber *xImuLcd = new QLCDNumber(this);
    xImuHBox->addWidget(xImu);
    xImuHBox->addWidget(xImuLcd);

    QHBoxLayout *yImuHBox = new QHBoxLayout;
    QLabel *yImu = new QLabel(tr("Roll"));
    QLCDNumber *yImuLcd = new QLCDNumber(this);
    yImuHBox->addWidget(yImu);
    yImuHBox->addWidget(yImuLcd);

    QHBoxLayout *zImuHBox = new QHBoxLayout;
    QLabel *zImu = new QLabel(tr("Yaw"));
    QLCDNumber *zImuLcd = new QLCDNumber(this);
    zImuHBox->addWidget(zImu);
    zImuHBox->addWidget(zImuLcd);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addLayout(xImuHBox);
    vbox->addLayout(yImuHBox);
    vbox->addLayout(zImuHBox);
    vbox->addStretch(1);
    imuGroupBox->setLayout(vbox);

    return imuGroupBox;
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void Window::readData()
{
    QByteArray temp = port->readAll();
    qDebug() << "read:" << temp;
}

void Window::sendData()
{
    QString str;

    str.append("abc999999999999999999999999999999999999999999999999999");
    port->write(str.toAscii());
    qDebug() << "send:" << str;
}
