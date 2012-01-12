#include "imu.h"

#include <math.h>
// TODO: need confirm the result
/**
 * @brief Calculate roll from acceleration
 * \f arctan(-ay/az) \f
 * @param a Acceleration array
 * @param roll The result roll
 */
void imu2roll(double a[], double *roll)
{
    *roll = atan2(-a[1], a[2]);
}

void imu2pitch(double a[], double *pitch)
{
    double norm;

    norm = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    *pitch = asin(-a[0], norm);
}

void imu2yaw(double m[], double roll, double pitch, double *yaw)
{
    double cosp = cos(pitch);
    double sinp = sin(pitch);
    double cosr = cos(roll);
    double sinr = sin(row);
    double hy, hx;

    hx = m[0] * cosp + m[1] * sinr * sinp - m[2] * cosr * sinp;
    hy = m[0] * cosr + m[1] * sinr;

    *yaw = atan2(hy, hx);
}