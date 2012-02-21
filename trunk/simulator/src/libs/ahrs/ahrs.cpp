#include "ahrs.h"

AHRS_EKF::AHRS_EKF()
{
    setDim(7, 3, 3, 3, 3);
    // initial state estimate
    x(1) = 1.0;
    x(2) = 0;
    x(3) = 0;
    x(4) = 0;
    x(5) = 0;
    x(6) = 0;
    x(7) = 0;
}

void AHRS_EKF::makeA()
{
    double q0 = x(1);
    double q1 = x(2);
    double q2 = x(3);
    double q3 = x(4);

    double p = gyro(1) - x(5);
    double q = gyro(2) - x(6);
    double r = gyro(3) - x(7);

    A(1, 1) = 1.0;
    A(1, 2) = -p * dt / 2;
    A(1, 3) = -q * dt / 2;
    A(1, 4) = -r * dt / 2;
    A(1, 5) = q1 * dt / 2;
    A(1, 6) = q2 * dt / 2;
    A(1, 7) = q3 * dt / 2;

    A(2, 1) = p * dt / 2;
    A(2, 2) = 1.0;
    A(2, 3) = r * dt / 2;
    A(2, 4) = -q * dt / 2;
    A(2, 5) = -q0 * dt / 2;
    A(2, 6) = q3 * dt / 2;
    A(2, 7) = -q2 * dt / 2;

    A(3, 1) = q * dt / 2;
    A(3, 2) = -r * dt / 2;
    A(3, 3) = 1.0;
    A(3, 4) = p * dt / 2;
    A(3, 5) = -q3 * dt / 2;
    A(3, 6) = -q0 * dt / 2;
    A(3, 7) = q1 * dt / 2;

    A(4, 1) = r * dt / 2;
    A(4, 2) = q * dt / 2;
    A(4, 3) = -p * dt / 2;
    A(4, 4) = 1.0;
    A(4, 5) = q2 * dt / 2;
    A(4, 6) = -q1 * dt / 2;
    A(4, 7) = -q0 * dt / 2;
}

void AHRS_EKF::makeH()
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

void AHRS_EKF::makeV()
{
}

void AHRS_EKF::makeR()
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

void AHRS_EKF::makeW()
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

void AHRS_EKF::makeQ()
{
}

void AHRS_EKF::makeProcess()
{
    Vector state(x.size());

    double p = u(1) - x(5);
    double q = u(2) - x(6);
    double r = u(3) - x(7);

    double q0 = x(1);
    double q1 = x(2);
    double q2 = x(3);
    double q3 = x(4);

    state(1) = (-p * q1 - q * q2 - r * q3) * dt / 2;
    state(2) = (p * q0 - q * q3 + r * q2) * dt / 2;
    state(3) = (p * q3 + q * q0 - r * q1) * dt / 2;
    state(4) = (-p * q2 + q * q1 + r * q0) * dt / 2;
    state(5) = 0;
    state(6) = 0;
    state(7) = 0;

    x(1) = x(1) + state(1);
    x(2) = x(2) + state(2);
    x(3) = x(3) + state(3);
    x(4) = x(4) + state(4);
    x(5) = x(5) + state(5);
    x(6) = x(6) + state(6);
    x(7) = x(7) + state(7);
}

void AHRS_EKF::makeMeasure()
{
    z(1) = x(1);
    z(2) = x(2);
    z(3) = x(3);
    z(4) = x(4);
}
