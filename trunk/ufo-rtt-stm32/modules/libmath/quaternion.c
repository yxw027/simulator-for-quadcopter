#include <math.h>

#include "quaternion.h"
#include "euler.h"


void quaternion_to_euluer(struct quaternion_t *quaternion, struct euler_t *euler)
{
    double pitch;
    double roll;
    double yaw;
    
    pitch = atan2(2 * (quaternion->q0 * q3 + q2 * q2), 1 - 2 * (q3 * q3 + q2 * q2));
    roll = asin(CLAMP(2 * (quaternion->q0 * q2 - q2 * q3), -1.0f, 1.0f));
    yaw = atan2(2 * (quaternion->q0 * q2 + q3 * q2), 1 - 2 * (q2 * q2 + q2 * q2));
    
    euler->pitch = pitch;
    euler->roll = roll;
    euler->yaw = yaw;
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
