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
 * @brief Initialize gyroscope
 *
 * @return none
 */
void gyro_hw_init();

/**
 * @brief Update gyro sensor data
 *
 * @param val Where to store the sensor data
 *
 * @return 0 success, negative otherwise
 */
int gyro_update_value(uint16_t val[3]);

/** @} */

/** @} */

#endif /* _IGYRO_H */