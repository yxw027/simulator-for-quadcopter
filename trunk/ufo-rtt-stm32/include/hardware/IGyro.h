/**
 * @file IGyro.h
 * Gyroscope Sensor Interface.
 */

#ifndef _IGYRO_H
#define _IGYRO_H

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup Hardware Abstract Layer
 * @{
 */

/**
 * @struct gyro_event_t
 * gyroscope sensor event
 */
typedef struct gyro_event_t {
    uint32_t gx;
    uint32_t gy;
    uint32_t gz;
} gyro_event_t;

typedef struct gyro_bias_t {
    uint32_t gyro_bias_x;
    uint32_t gyro_bias_y;
    uint32_t gyro_bias_z;
} gyro_bias_t;

typedef struct gyro_sensor_t {
    struct gyro_event_t value;
    struct gyro_bias_t offset;
} gyro_sensor_t;

/**
 * Initialize gyroscope
 *
 * @return none
 */
void init_hw_gyro();
 
/**
 * Get gyro raw data
 *
 * @param pointer to gyro event
 *
 * @return 0 success, negative otherwise
 */
int gyro_get_value(struct gyro_event_t *event);

/** @} */

/** @} */

#endif /* _IGYRO_H */