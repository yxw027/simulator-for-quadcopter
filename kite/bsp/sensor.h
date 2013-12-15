/**
 * @file sensor.h
 * @brief sensor IO interface
 */

/**
 * sensor type definition
 */
enum sensor_type {
	SENSOR_TYPE_ACCEL = 0,
	SENSOR_TYPE_GYRO,
	SENSOR_TYPE_MAG,
    SENSOR_TYPE_MPU6000,
	SENSOR_TYPE_GPS,
	SENSOR_TYPE_MAX,
};

#pragma anon_unions
typedef union sensor_data {
    struct {
        float x, y, z;	/* for 3-axis sensors */
    };
    char value[16];		/* for other sensors, e.g GPS */
} sensor_data_t;

typedef struct sensor {
	enum sensor_type type;
    const char *name;	/* reserved */
    sensor_data_t data;
} sensor_t;

void sensor_init(void);
