/**
 * @file IGyro.h
 * Gyroscope Sensor Interface.
 */

 typedef struct gyro_event_t {
    uint32_t x;
    uint32_t y;
    uint32_t z;
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
 * Get gyro raw data
 *
 * @param pointer to gyro event
 *
 * @return 0 success, negative otherwise
 */
int gyro_get_value(struct gyro_event_t *event);
 