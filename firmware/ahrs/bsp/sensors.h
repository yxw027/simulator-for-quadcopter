/**
 * @file sensor.h
 * @brief sensor IO interface
 */

/**
 * sensor ID definition
 */
#define SENSOR_ID_ACCEL     0
#define SENSOR_ID_GYRO      1
#define SENSOR_ID_MAG       2
#define SENSOR_ID_MAX       3

typedef struct sensor_event_t {
    union {
        float val[3];
        struct {
            float x, y, z;
        };
    };
} sensor_event_t;

typedef struct sensor_t {
    int id;
    char *name;
    /* ops */
    int (*init)(sensor_t *sensor);
    int (*read)(sensor_t *sensor, char *buf, int len);
    int (*write)(sensor_t *sensor, char *buf, int len);
    int (*ioctl)(sensor_t *sensor, int cmd, void *arg);
    int (*poll)(sensor_t *sensor, sensor_event_t *event);

    void *driv_data;
} sensor_t;


/**
 * @brief Read from a buffer
 *
 * @param buf Where the data read from
 * @param len
 * @retval The bytes size read, negetive if error occurs
 */
int sensor_read(int id, char *buf, int len);

int sensor_write(int id, char *buf, int len);

int sensor_ioctl(int id, int cmd, void *arg);

int sensor_poll(int id, sensor_event_t *event);
