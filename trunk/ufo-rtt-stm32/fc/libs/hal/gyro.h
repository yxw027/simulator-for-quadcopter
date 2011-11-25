/**
 * @file gyro.h
 * @brief Gyroscope Sensor Interface.
 */

#ifndef _GYRO_H
#define _GYRO_H

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup HAL
 * @{
 */

/**
 * @struct gyro_event_t
 * gyroscope sensor event
 */
typedef struct gyro_event_t {
    uint32_t x;     /**< x-axis value of gyro */
    uint32_t y;     /**< y-axis value of gyro */
    uint32_t z;     /**< z-axis value of gyro */
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