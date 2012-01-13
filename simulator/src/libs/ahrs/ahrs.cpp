#include "ahrs.h"

AHRS_EKF::AhrsEKF()
{
    setDim(7, 3, 3, 3, 3);
}

void AHRS_EKF::makeA()
{
    A(1, 1) = 1.0;
    A(1, 2) = 0.0;
    A(1, 3) = 0.0;
    A(1, 4) = 0.0;
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


