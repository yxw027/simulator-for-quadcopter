/**
 * @file sensor.h
 * @brief sensor IO interface
 */

/**
 * sensor id
 */ 
#define SENSOR_ID_MIN       0
#define SENSOR_ID_ACCEL     1
#define SENSOR_ID_GYRO      2
#define SENSOR_ID_MAG       3
#define SENSOR_ID_MAX       4

/**
 * ioctl commands
 */
#define IOC_READ            0
#define IOC_WRITE           1

struct sensor_t {
    int id;
    char *name;
    /* ops */
    int (*init)(struct sensor_t *sensor, void *arg);
    int (*read)(char *buf, int len);
    int (*write)(char *buf, int len);
    int (*ioctl)(int cmd, void *arg);

    void *priv_data;
};

typedef struct sensor_event_t {
    union {
        x, y, z
    } val;
} sensor_event;

int sensor_read(int id, char *buf, int len);

int sensor_write(int id, char *buf, int len);

int sensor_ioctl(int id, int cmd, void *arg);

