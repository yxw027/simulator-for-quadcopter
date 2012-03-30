/**
 * @file quaternion.c
 * @brief quaternion implementation
 */

#include "math.h"

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup math
 * @{
 */

void quaternion2euler(double euler[3], double q[4])
{
    double q0 = q[0];
    double q1 = q[1];
    double q2 = q[2];
    double q3 = q[3];

    double phi;
    double theta;
    double psi;

    phi = atan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (q1 * q1 + q2 * q2));
    theta = asin(LIMIT(2 * (q0 * q2 - q1 * q3), -1.0f, 1.0f));
    psi = atan2(2 * (q0 * q3 + q1 * q2), 1 - 2 * (q2 * q2 + q3 * q3));

    euler[0] = phi;
    euler[1] = theta;
    euler[2] = psi;
}

void quaternion_normalize(double q[4])
{
    double norm;
    double q0 = q[0];
    double q1 = q[1];
    double q2 = q[2];
    double q3 = q[3];

    norm = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);

    q[0] = q0 / norm;
    q[1] = q1 / norm;
    q[2] = q2 / norm;
    q[3] = q3 / norm;
}

/** @} */

/** @} */
