/**
 * @file imufilter.h
 * IMU orientation filter.
 */

#ifndef _IMUFILTER_H
#define _IMUFILTER_H#include "euler.h"
/** * @addtogroup ufo * @{ *//** * @addtogroup imu * @{ */
/**
 * imu filter update
 *
 * @return None
 */
imufilter_update(void);

/**
 * Get the current roll.
 *
 * @return The current roll angle in radians.
 */
double get_roll(void);
/** @} *//** @} */
#endif /* _IMUFILTER_H */