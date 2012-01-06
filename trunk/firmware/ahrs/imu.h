/**
 * @file imu.h
 * @brief IMU module interface
 */

#ifndef _IMU_H
#define _IMU_H

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup imu
 * @{
 */

#include "bsp/accel.h"
#include "bsp/gyro.h"
#include "bsp/mag.h"


/**
 * Convert euler to quaternion, for details see page \ref euler
 *
 */
void euler2quat(struct quat_t *quat, struct euler_t *euler);
void quat2euler(double quat[], double *theta, double *psi, double *phi);

/** @} */

/** @} */

#endif /* _IMU_H */