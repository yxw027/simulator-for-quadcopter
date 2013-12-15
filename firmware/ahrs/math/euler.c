/**
 * @file euler.c
 * @brief euler math implementation
 */

#include "math.h"

void euler2quaternion(double q[4], double euler[3])
{
    double c1 = cos(euler->yaw / 2);
    double s1 = sin(euler->yaw / 2);
    double c2 = cos(euler->pitch / 2);
    double s2 = sin(euler->pitch / 2);
    double c3 = cos(euler->roll / 2);
    double s3 = sin(euler->roll / 2);

    quat->w = c1 * c2 * c3 - s1 * s2 * s3;
    quat->x = c1 * c2 * s3 + s1 * s2 * c3;
    quat->y = s1 * c2 * c3 + c1 * s2 * s3;
    quat->z = c1 * s2 * s3 - s1 * c2 * c3;
}