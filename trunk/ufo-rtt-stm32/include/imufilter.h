/**
 * @file imufilter.h
 * IMU orientation filter.
 */

#ifndef _IMUFILTER_H
#define _IMUFILTER_H


/**
 *
 */
typedef struct orientation_t {
    uint32_t pitch;
    uint32_t roll;
    uint32_t yaw;
} orientation_t;
    
/**
 * Compute the Euler angles based on the current filter data.
 *
 * @param orientation orientation to be updated
 * @return 0 success, negative otherwise
 */ 
int IMUfilter_computeEnler(struct orientation_t *orientation)
{
}

/**
 * Get the current roll.
 *
 * @return The current roll angle in radians.
 */
 double getRoll(void);

/**
 * Get the current pitch.
 *
 * @return The current pitch angle in radians.
 */
double getPitch(void);

/**
 * Get the current yaw.
 *
 * @return The current yaw angle in radians.
 */
double getYaw(void);

#endif /* _IMUFILTER_H */