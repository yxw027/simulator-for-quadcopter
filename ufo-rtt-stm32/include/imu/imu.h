/**
 * @file imu.h
 * imu module interface
 */

#ifndef _IMU_H
#define _IMU_H

#include "euler.h"

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup imu
 * @{
 */
/**
 * imu orientation update
 * 
 * @param gx x-axis value of gyro
 * @param gy y-axis value of gyro
 * @param gz z-axis value of gyro
 * @param ax x-axis value of accelerometer
 * @param ay y-axis value of accelerometer
 * @param az z-axis value of accelerometer
 * 
 * @retval None
 * @note TODO
 */
void imu_update(float gx, float gy, float gz, float ax, float ay, float az);
/** @} */

/** @} */

#endif /* _IMU_H */