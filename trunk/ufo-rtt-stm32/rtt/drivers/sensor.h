/**
 * @file sensors.h
 * @brief sensor IO interface
 */

#include <stm32f10x.h>


/**
 * sensor ID definition
 */
#define SENSOR_ID_ACCEL     0
#define SENSOR_ID_GYRO      1
#define SENSOR_ID_MAG       2
#define SENSOR_ID_MAX       3


struct sensor_event {
    uint16_t val[3];
    struct {
        uint16_t x, y, z;
    } vec;
};

struct sensor {
    int id;
    struct sensor_event event;
};
