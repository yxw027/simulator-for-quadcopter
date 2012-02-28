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

#define AXIS_X      0
#define AXIS_Y      1
#define AXIS_Z      2
#define AXIS_MAX    3

/**
 * Convert euler to quaternion, for details see page \ref euler
 *
 */
/**
 * @brief Convert euler angle to quaternion
 * @param phi Roll angle in radians
 * @param theta Pitch angle in radians
 * @param psi Yaw angle in radians
 * @param quat quaternion vector
 * @return None
 */
void euler2quat(double phi, double theta, double psi, double quat[]);
/**
 * @brief Convert quaternion angle to euler
 * @param quat quaternion vector 
 * @param phi Roll angle in radians
 * @param theta Pitch angle in radians
 * @param psi Yaw angle in radians
 * @return None
 */
void quat2euler(double quat[4], double euler[3]);

int imu_get_accels(double value[]);
int imu_get_gyros(double value[]);
int imu_get_mags(double value[]);
/**
 * @brief Calculate roll from acceleration
 * \f arctan(ay/ax) \f
 * @param a Acceleration data
 * @param roll The result roll
 * @return None
 */
void imu2roll(double a[], double *roll);

/**
 * @brief Calculate pitch from acceleration
 * @param a Acceleration data
 * @param pitch The result pitch
 * @return None
 */
void imu2pitch(double a[], double *pitch);

/**
 * @brief Calculate yaw(or heading) from 3-axis earth magnetic field \f [mx my mz \f \n
 * and roll, pitch angle using the following equation: \n
 * \f hx = mx * cos \theta + my * sin \theta * sin \f TODO...
 */
void imu2yaw(double m[], double roll, double pitch, double *yaw);

/** @} */

/** @} */

#endif /* _IMU_H */