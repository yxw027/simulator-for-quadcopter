#include "ahrs.h"

AHRS_EKF::AhrsEKF()
{
    setDim(7, 3, 3, 3, 3);
}

void AHRS_EKF::makeA()
{
    double p, q, r;

    p = gx - x(5);
    q = gy - x(6);
    r = gz - x(7);

    A(1, 1) = 1.0;
    A(1, 2) = -p * dt / 2;
    A(1, 3) = -q * dt / 2;
    A(1, 4) = -r * dt / 2;
    A(1, 5) = quat[1]  * dt / 2;
    A(1, 6) = quat[2]  * dt / 2;
    A(1, 7) = quat[3] * dt / 2;

    A(2, 1) = p * dt / 2;
    A(2, 2) = 1.0;
    A(2, 3) = r * dt / 2;
    A(2, 4) = -q * dt / 2;
    A(2, 5) = -quat[0] * dt / 2;
    A(2, 6) = quat[3] * dt / 2;
    A(2, 7) = -quat[2] * dt / 2;

    A(3, 1) = q * dt / 2;
    A(3, 2) = -r * dt / 2;
    A(3, 3) = 1.0;
    A(3, 4) = p * dt / 2;
    A(3, 5) = -quat[3] * dt / 2;
    A(3, 6) = -quat[0] * dt / 2;
    A(3, 7) = quat[1] * dt / 2;

    A(4, 1) = r * dt / 2;
    A(4, 2) = q * dt / 2;
    A(4, 3) = -p * dt / 2;
    A(4, 4) = 1.0;
    A(4, 5) = quat[2] * dt / 2;
    A(4, 6) = -quat[1] * dt / 2;
    A(4, 7) = -quat[0] * dt / 2;
}

void AHRS_EKF::makeProcess()
{
    //Vector;
}

void AHRS_EKF::makeMeasure()
{
    z(1) = atan2(x(1), x(2));
    z(2) = asin();
    z(3) = atan2();
}


