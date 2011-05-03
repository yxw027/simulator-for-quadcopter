#include "imu.h"

#include <QTimer>

Imu::Imu(float imuRate,
         double gyroscopeMeasurementError,
         float accelerometerRate,
         float gyroscopeRate) :
         //accelerometer(p5, p6, p7, p8),
         //gyroscope(p9, p10),
         imuFilter(imuRate, gyroscopeMeasurementError)
{
    accelerometerTicker = new QTimer(this);
    connect(accelerometerTicker, SIGNAL(timeout()), this, SLOT(sampleAccelerometer()));
    gyroscopeTicker = new QTimer(this);
    connect(gyroscopeTicker, SIGNAL(timeout()), this, SLOT(sampleGyroscope()));
    filterTicker = new QTimer(this);
    connect(filterTicker, SIGNAL(timeout()), this, SLOT(filter()));

    accelerometerTicker->start(accelerometerRate);
    gyroscopeTicker->start(gyroscopeRate);
    filterTicker->start(imuRate);
}

double Imu::getRoll(void)
{
    return toDegrees(imuFilter.getRoll());
}

double Imu::getPitch(void)
{
    return toDegrees(imuFilter.getPitch());
}

double Imu::getYaw(void)
{
    return toDegrees(imuFilter.getYaw());
}

void Imu::initializeAccelerometer(void)
{
    //Go into standby mode to configure the device.
    accelerometer.setPowerControl(0x00);
    //Full resolution, +/-16g, 4mg/LSB.
    accelerometer.setDataFormatControl(0x0B);
    //200Hz data rate.
    accelerometer.setDataRate(ADXL345_200HZ);
    //Measurement mode.
    accelerometer.setPowerControl(0x08);
    //See http://www.analog.com/static/imported-files/application_notes/AN-1077.pdf
    wait_ms(22);
}

void Imu::filter(void)
{
    //Update the filter variables.
    imuFilter.updateFilter(g_y, g_x, g_z, a_y, a_x, a_z);
    //Calculate the new Euler angles.
    imuFilter.computeEuler();
}

double getGyroX(void)
{
    return g_x;
}

double getGyroY(void)
{
    return g_y;
}

double getGyroZ(void)
{
    return g_z;
}

double getAcclX(void)
{
    return a_x;
}

double getAcclY(void)
{
    return a_y;
}

double getAcclZ(void)
{
    return a_z;
}
