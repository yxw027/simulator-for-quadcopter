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

typedef union sensor_event {
    float val[3];
    struct {
        float x, y, z;
    };
} sensor_event_t;

typedef struct sensor {
    int id;
    char *name;
    /* ops */
    int (*init)(struct sensor *sensor);
    int (*read)(struct sensor *sensor, char *buf, int len);
    int (*write)(struct sensor *sensor, char *buf, int len);
    int (*ioctl)(struct sensor *sensor, int cmd, void *arg);
    int (*poll)(struct sensor *sensor, sensor_event_t *event);

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
