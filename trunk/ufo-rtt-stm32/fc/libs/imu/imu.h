/**
 * @file imu.h
 * @brief IMU module interface
 */

#ifndef _IMU_H
#define _IMU_H

#include "hal/accel.h"
#include "math/euler.h"

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup imu
 * @{
 */

/**
 * helper definitions
 */
#define GET_PITCH(accel)    (accel->pitch)
#define GET_ROLL(accel)     (accel->roll)
#define GET_YAW(accel)      (accel->yaw)

/**
 * IMU orientation update
 * 
 * @param g Values of gyro
 * @param a Values of accelerometer
 * @retval None
 * @note TODO
 */
void imu_update(gyro_event_t g, accel_event_t a);

/**
 * Get the euler angle from accelerometer at inital state, according to the following formula(s): \n
 * Pitch \f$ \rho \f$ defined as \f[ \rho = \arctan(\frac{A_x}{\sqrt{A_y^2+A_z^2}}) \f]
 * Roll \f$ \psi \f$ defined as \f[ \psi = \arctan(\frac{A_y}{\sqrt{A_x^2+A_z^2}}) \f]
 * Theta \f$ \theta \f$ defined as \f[ \theta = arctan(\frac{\sqrt{A_x^2+A_y^2}}{Az}) \f]
 * @param accel The pointer to the accelerometer raw data
 * @param euler The point to euler angle
 * @return None
 * @note The funtion only be used when the flight is not in motion
 */
void accel2euler(struct accel_event_t *accel, struct euler_t *euler);

/** @} */

/** @} */

#endif /* _IMU_H */