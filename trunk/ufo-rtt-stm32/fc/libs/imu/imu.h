/**
 * @file imu.h
 * @brief IMU module interface
 */

#ifndef _IMU_H
#define _IMU_H

#include "hal/accel.h"
#include "hal/gyro.h"

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

typedef struct imu_t {
    accel_event_t   accel;
    accel_offset_t  accel_offset;
    
    gyro_event_t    gyro;
    gyro_bias_t     gyro_bias;
} imu_t;

/**
 * Initialize IMU
 *
 * @return 0 if success, negative otherwise
 */
int init_IMU();

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
 * Pitch \f$ \rho \f$ defined as \f[ \rho = \arctan \left( \frac{A_x}{\sqrt{A_y^2+A_z^2}} \right) \f]
 * Roll \f$ \psi \f$ defined as \f[ \psi = \arctan \left( \frac{A_y}{\sqrt{A_x^2+A_z^2}} \right) \f]
 * Theta \f$ \theta \f$ defined as \f[ \theta = arctan \left( \frac{\sqrt{A_x^2+A_y^2}}{Az} \right) \f]
 * @param accel The pointer to the accelerometer raw data
 * @param euler The point to euler angle
 * @return None
 * @note The funtion only be used when the flight is not in motion
 */
void accel2euler(struct accel_event_t *accel, struct euler_t *euler);

/** @} */

/** @} */

#endif /* _IMU_H */