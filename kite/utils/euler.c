/**
 * @file euler.c
 * @brief euler math implementation
 */

#include <math.h>

void euler_to_quaternion(struct euler *e, struct quaternion *q)
{
    double c1 = cos(e->yaw / 2);
    double s1 = sin(e->yaw / 2);
    double c2 = cos(e->pitch / 2);
    double s2 = sin(e->pitch / 2);
    double c3 = cos(e->roll / 2);
    double s3 = sin(e->roll / 2);

    q->w = c1 * c2 * c3 - s1 * s2 * s3;
    q->x = c1 * c2 * s3 + s1 * s2 * c3;
    q->y = s1 * c2 * c3 + c1 * s2 * s3;
    q->z = c1 * s2 * s3 - s1 * c2 * c3;
}