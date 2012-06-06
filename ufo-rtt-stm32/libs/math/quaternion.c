/**
 * @file quaternion.c
 * quaternion implementation
 */
#include <math.h>

#include "quaternion.h"
#include "euler.h"

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup math
 * @{
 */

void quaternion2euler(struct quat_t *quat, struct euler_t *euler)
{
    double pitch;
    double roll;
    double yaw;
    
    roll = atan2(2 * (quaternion->q0 * q1 + q2 * q3), 1 - 2 * (q1 * q1 + q2 * q2));
    pitch = asin(CLAMP(2 * (quaternion->q0 * q2 - q1 * q3), -1.0f, 1.0f));
    yaw = atan2(2 * (quaternion->q0 * q3 + q1 * q2), 1 - 2 * (q2 * q2 + q3 * q3));
    
    euler->pitch = pitch;
    euler->roll = roll;
    euler->yaw = yaw;
}

void quaternion_from_euler(struct euler_t *euler, struct quaternion_t *quad)
{
    double c1, c2, c3, s1, s2, s3;
    
    c2 = cos(euler->pitch / 2);
    c1 = cos(euler->roll / 2);
    c3 = cos(euler->yaw / 2);
    s1 = sin(euler->roll / 2);
    s2 = sin(euler->pitch / 2);
    s3 = sin(euler->yaw / 2);
/*
    quad->w = c1 * c2 * c3 - s1 * s2 * s3;
    quad->x = s1 * s2 * c3 + c1 * c2 * s3;
    quad->y = s1 * c2 * c3 + c1 * s2 * s3;
    quad->z = c1 * s2 * c3 - s1 * c2 * s3;*/
    quad->q0 = c1 * c2 * c3 + s1 * s2 * s3;
    quad->q1 = s1 * c2 * c3 - c1 * s2 * s3;
    quad->q2 = c1 * s2 * c3 + s1 * c2 * s3;    
    quad->q3 = c1 * c2 * s3 - s1 * s2 * c3;
}

void quat_norm(struct quat_t *q)
{
    double norm;
    
    norm = sqrt(q->q0 * q->q0 +
                q->q1 * q->q1 +
                q->q2 * q->q2 +
                q->q3 * q->q3);
    q->q0 /= norm;
    q->q1 /= norm;
    q->q2 /= norm;
    q->q3 /= norm; 
}
/*
void quat_mult(quat_t *l, quat_t *r, quat_t *out)
{
    out->w = l->w * r->w - l->x * l->x - l->y * r->y - l->z * r->z;
    out->x = l->w * r->x + l->x * r->w + l->y * r->z - l->z * r->y;
    out->y = l->w * r->y + l->y * r->w + l->z * r->x - l->x * r->z;
    out->z = l->w * r->z + l->z * r->w + l->x * r->y - l->y * r->x;
}
*/
void quat_mult(quat_t *l, quat_t *r, quat_t *out)
{
    out[0] = l[0] * r[0] - l[1] * l[1] - l[2] * r[2] - l[3] * r[3];
    out[1] = l[0] * r[1] + l[1] * r[0] + l[2] * r[3] - l[3] * r[2];
    out[2] = l[0] * r[2] + l[2] * r[0] + l[3] * r[1] - l[1] * r[3];
    out[3] = l[0] * r[3] + l[3] * r[0] + l[1] * r[2] - l[2] * r[1];
}

/** @} */

/** @} */
