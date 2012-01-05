#include "bsp/accel.h"
#include "bsp/gyro.h"
#include "bsp/mag.h"

#define SENSOR_TYPE_ACCEL
#define SENSOR_TYPE_GYRO
#define SENSOR_TYPE_MAG
#define SENSOR_TYPE_GPS

typedef struct sensor_event_t
    int type;
    uint32_t x;
    uint32_t y;
    uint32_t z;
} sensor_event_t;

typedef struct sensor_t {
    int type;
    char *name;
    int value[ACCEL_MAX];
    uint32_t accel[ACCEL_MAX];
    uint32_t gyro[GYRO_MAX];
    uint32_t mag[MAG_MAX];
} sensor_t;