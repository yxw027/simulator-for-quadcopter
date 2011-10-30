#include "imufilter.h"

#include "math/quaternion.h"

int IMUfilter_computeEnler(struct quaternion_t *quaternion, struct estimated_quaternion_t *est, struct orientation_t *orientation)
{
    int retval = 0;
    //FIXME data type
    double phi;
    double theta;
    double psi;
    
    //Quaternion describing orientation of sensor relative to earth.
    double ESq_1, ESq_2, ESq_3, ESq_4;
    //Quaternion describing orientation of sensor relative to auxiliary frame.
    double ASq_1, ASq_2, ASq_3, ASq_4;

    //Compute the quaternion conjugate.
    ESq_1 =  est->SEq_1;
    ESq_2 = -est->SEq_2;
    ESq_3 = -est->SEq_3;
    ESq_4 = -est->SEq_4;
    
    //Compute the quaternion product.
    ASq_1 = ESq_1 * quaternion->q0 - ESq_2 * AEq_2 - ESq_3 * AEq_3 - ESq_4 * AEq_4;
    ASq_2 = ESq_1 * AEq_2 + ESq_2 * quaternion->q0 + ESq_3 * AEq_4 - ESq_4 * AEq_3;
    ASq_3 = ESq_1 * AEq_3 - ESq_2 * AEq_4 + ESq_3 * quaternion->q0 + ESq_4 * AEq_2;
    ASq_4 = ESq_1 * AEq_4 + ESq_2 * AEq_3 - ESq_3 * AEq_2 + ESq_4 * quaternion->q0;
    
    //Compute the Euler angles from the quaternion.
    phi   = atan2(2 * ASq_3 * ASq_4 - 2 * ASq_1 * ASq_2, 2 * ASq_1 * ASq_1 + 2 * ASq_4 * ASq_4 - 1);
    theta = asin (2 * ASq_2 * ASq_3 - 2 * ASq_1 * ASq_3);
    psi   = atan2(2 * ASq_2 * ASq_3 - 2 * ASq_1 * ASq_4, 2 * ASq_1 * ASq_1 + 2 * ASq_2 * ASq_2 - 1);

    orientation->pitch = theta;
    orientation->roll = phi;
    orientation->yaw = psi;
    
    return retval;
}
