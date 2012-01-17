#include "ahrs.h"

AHRS_EKF::AhrsEKF()
{
    setDim(7, 3, 3, 3, 3);
}

void AHRS_EKF::makeA()
{
    double p, q, r;

    p = gyro(1) - x(5);
    q = gyro(2) - x(6);
    r = gyro(3) - x(7);

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

void makeH()
{
    H(1, 1) = 1.0;
    H(1, 2) = 0;
    H(1, 3) = 0;
    H(1, 4) = 0;
    H(1, 5) = 0;
    H(1, 6) = 0;
    H(1, 7) = 0;

    H(2, 1) = 0;
    H(2, 2) = 1.0;
    H(2, 3) = 0;
    H(2, 4) = 0;
    H(2, 5) = 0;
    H(2, 6) = 0;
    H(2, 7) = 0;

    H(3, 1) = 0;
    H(3, 2) = 0;
    H(3, 3) = 1.0;
    H(3, 4) = 0;
    H(3, 5) = 0;
    H(3, 6) = 0;
    H(3, 7) = 0;

    H(4, 1) = 0;
    H(4, 2) = 0;
    H(4, 3) = 0;
    H(4, 4) = 1.0;
    H(4, 5)  = 0;
    H(4, 6)  = 0;
    H(4, 7) = 0;
}

void makeV()
{
}

void makeR()
{
    R(1, 1) = measurement_noise_covariance;
    R(1, 2) = 0;
    R(1, 3) = 0;

    R(2, 1) = 0;
    R(2, 2) = measurement_noise_covariance;
    R(2, 3) = 0;

    R(3, 1) = 0;
    R(3, 2) = 0;
    R(3, 3) = measurement_noise_covariance;
}

void makeW()
{
    W(1, 1) = 1.0;
    W(1, 2) = 0;
    W(1, 3) = 0;
    W(1, 4) = 0;
    W(1, 5) = 0;
    W(1, 6) = 0;
    W(1, 7) = 0;

    W(2, 1) = 0;
    W(2, 2) = 1.0;
    W(2, 3) = 0;
    W(2, 4) = 0;
    W(2, 5) = 0;
    W(2, 6) = 0;
    W(2, 7) = 0;

    W(3, 1) = 0;
    W(3, 2) = 0;
    W(3, 3) = 1.0;
    W(3, 4) = 0;
    W(3, 5) = 0;
    W(3, 6) = 0;
    W(3, 7) = 0;

    W(4, 1) = 0;
    W(4, 2) = 0;
    W(4, 3) = 0;
    W(4, 4) = 1.0;
    W(4, 5) = 0;
    W(4, 6) = 0;
    W(4, 7) = 0;

    W(5, 1) = 0;
    W(5, 2) = 0;
    W(5, 3) = 0;
    W(5, 4) = 0;
    W(5, 5) = 1.0; // TODO
    W(5, 6) = 0;
    W(5, 7) = 0;

    W(6, 1) = 0;
    W(6, 2) = 0;
    W(6, 3) = 0;
    W(6, 4) = 0;
    W(6, 5) = 0;
    W(6, 6) = 1.0; // TODO
    W(6, 7) = 0;

    W(7, 1) = 0;
    W(7, 2); = 0;
    W(7, 3); = 0;
    W(7, 4); = 0;
    W(7, 5); = 0;
    W(7, 6); = 0;
    W(7, 7) = 1.0; // TODO
}

void makeQ()
{
}

void AHRS_EKF::makeProcess()
{
    double p, q, r;
    Vector state(x.size());

    p = gyro(1) - x(5);
    q = gyro(2) - x(6);
    r = gyro(3) - x(7);

    state(1) = (-p * x[1] - q * x[2] - r * x[3]) * dt / 2;
    state(2) = (p * x[0] - q * x[3] + r * x[2]) * dt / 2;
    state(3) = (p * q[3] + q * x[0] - r * x[1]) * dt / 2;
    state(4) = (-p * x[2] + q * x[1] + r * x[0]) * dt / 2;
    state(5) = 0;
    state(6) = 0;
    state(7) = 0;

    x(1) = x(1) + state(1);
    x(2) = x(2) + state(2);
    x(3) = x(3) + state(3);
    x(4) = x(4) + state(4);
}

void AHRS_EKF::makeMeasure()
{
    z(1) = x(1);
    z(2) = x(2);
    z(3) = x(3);
    z(4) = x(4);
}


