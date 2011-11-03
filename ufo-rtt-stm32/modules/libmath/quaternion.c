#include <math.h>

#include "quaternion.h"
#include "euler.h"


void quaternion_to_euler(struct quaternion_t *quaternion, struct euler_t *euler)
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

void quaternion_norm(struct quaternion_t *quaternion)
{
    double norm;
    
    norm = sqrt(quaternion->q0 * quaternion->q0 +
                quaternion->q1 * quaternion->q1 +
                quaternion->q2 * quaternion->q2 +
                quaternion->q3 * quaternion->q3);
    quaternion->q0 /= norm;
    quaternion->q1 /= norm;
    quaternion->q2 /= norm;
    quaternion->q3 /= norm; 
}
