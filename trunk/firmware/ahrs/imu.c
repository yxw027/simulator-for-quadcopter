#include "imu.h"

#include <math.h>
// TODO: need confirm the result, Testing using hardware

void imu2roll(double a[], double *roll)
{
    double ax = a[0];
    double ay = a[1];

    *roll = arctan(ay, ax);
}

void imu2pitch(double a[], double *pitch)
{
    double g;
    double ax = a[0];
    double ay = a[1];
    double az = a[2];

    g = sqrt(ax * ax + ay * ay + az * az);
    *pitch = asin(-ax, g);
}

void imu2yaw(double m[], double roll, double pitch, double *yaw)
{
    double mx = m[0];
    double my = m[1];
    double mz = m[2];
    double cosp = cos(pitch);
    double sinp = sin(pitch);
    double cosr = cos(roll);
    double sinr = sin(row);
    double hy, hx;

    hx = mx * cosp + my * sinr * sinp - mz * cosr * sinp;
    hy = my * cosr + mz * sinr;

    *yaw = atan2(hy, hx);
}

void euler2quat(double roll, double pitch, double yaw, double q[])
{
    double cosy = cos(yaw / 2);
    double siny = sin(yaw / 2);
    double cosp = cos(pitch / 2);
    double sinp = sin(pitch / 2);
    double cosr = cos(roll / 2);
    double sinr = sin(roll / 2);
/*
    q[0] = cosp * cosr * cosy + sinp * sinr * siny;
    q[1] = sinp * cosr * cosy - cosp * sinr * siny;
    q[2] = cosp * sinr * cosy - sinp * cosr * siny;
    q[3] = cosp * cosr * sinr - sinp * sinr * cosy;
*/
    q[0] = cosp * cosr * cosy + sinp * sinr * siny;
    q[1] = cosp * sinr * cosy - sinp * cosr * siny;
    q[2] = sinp * cosr * cosy + cosp * sinr * siny;
    q[3] = cosp * cosr * sinr - sinp * sinr * cosy;
}

void quat2euler(double q[], double *phi, double *theta, double *psi)
{
#ifndef USING_EULER
    roll = atan2(2 * (q[0] * q[1] + q[2] * q[3]), 1 - 2 * (q[1] * q[1] + q[2] * q[2]));
    pitch = asin(CLAMP(2 * (q[1] * q[3] - q[0] * q[2]), -1.0f, 1.0f));
    yaw = atan2(2 * (q[0] * q[3] + q[1] * q[2]), 1 - 2 * (q[2] * q[2] + q[3] * q[3]));
#else
    *phi = atan2(2 *);
    *theta =;
    *psi =;
#endif   
}
