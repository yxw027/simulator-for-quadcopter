#include "imu.h"

#include <math.h>
// TODO: need confirm the result, Testing using hardware

/**
 * The local earth gravity, get from accelerometer when calibration
 */
float gravity;

uint32_t gyro[AXIS_MAX];
uint32_t accel[AXIS_MAX];
uint32_t mag[AXIS_MAX];

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
    double q0 = q[0];
    double q1 = q[1];
    double q2 = q[2];
    double q3 = q[3];
#ifndef USING_EULER
    roll = atan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (q1 * q1 + q2 * q2));
    pitch = -asin(2 * (q1 * q3 - q0 * q2));
    yaw = atan2(2 * (q0 * q3 + q1 * q2), 1 - 2 * (q2 * q2 + q3 * q3));
#else
    *phi = atan2(2 *);
    *theta =;
    *psi =;
#endif   
}

void quat2DCM(double q[], double DCM[3][3])
{
    double q0 = q[0];
    double q1 = q[1];
    double q2 = q[2];
    double q3 = q[3];

    DCM[0][0] = 1 - 2 * (q2 * q2 + q3 * q3);
    DCM[0][1] = 2 * (q1 * q2 + q0 * q3);
    DCM[0][2] = 2 * (q1 * q3 - q0 * q2);
    DCM[1][0] = 2 * (q1 * q2 - q0 * q3);
    DCM[1][1] = 1 - 2 * (q1 * q1 + q3 * q3);
    DCM[1][2] = 2 * (q2 * q3 + q0 * q1);
    DCM[2][0] = 2 * (q1 * q3 + q0 * q2);
    DCM[2][1] = 2 * (q2 * q3 - q0 * q1);
    DCM[2][2] = 1 - 2 * (q1 * q1 + q2 * q2);
}

/**
 * @brief The steady parameter
 *
 * @param None
 * @return Return 0 if not steady, positive otherwise
 */
int steady()
{
    uint16_t ax;
    uint16_t ay;
    uint16_t az;
    float gm = sqrt(ax * ax + ay * ay + az * az);
    float threshold = G_THRESHOLD;
    float percentage = abs((gm - gravity) / gravity);
    float deviation;

    da = accel_get_raw(ACCEL_X) - ax;
    dy = accel_get_raw(ACCEL_Y) - ay;
    dz = accel_get_raw(ACCEL_Z) - az;

    deviation = (1 - sqrt(da * da + dy * dy + dz * dz)) * 100.0;

    if ((percentage <= threshold) && )
        return 0;
    else
        return 1;
}