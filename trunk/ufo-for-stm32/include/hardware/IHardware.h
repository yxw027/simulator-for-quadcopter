#define SENSOR_TYPE_ACCL
#define SENSOR_TYPE_GYRO
#define SENSOR_TYPE_MARG
#define SENSOR_TYPE_GPS

typedef struct sensor_event_t
    int type;
    uint32_t x;
    uint32_t y;
    uint32_t z;
} sensor_event_t;