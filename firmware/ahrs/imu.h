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

int imu_update(struct sensor_event *event);

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