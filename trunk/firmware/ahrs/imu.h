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

int imu_get_accels(double value[]);
int imu_get_gyros(double value[]);
int imu_get_mags(double value[]);

void imu2roll(double a[], double *roll);
void imu2pitch(double a[], double *pitch);
void imu2yaw(double m[], double roll, double pitch, double *yaw);

/** @} */

/** @} */

#endif /* _IMU_H */