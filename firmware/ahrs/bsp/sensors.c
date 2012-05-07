#include "sensor.h"

sensor_t *sensors[SENSOR_ID_MAX];

int sensor_read(int id, char *buf, int len)
{
    if (id > SENSOR_ID_MAX)
        return -EINVAL;

    sensors[id]->read(sensors[id], buf, len);
}

int sensor_write(int id, char *buf, int len)
{
    if (id > SENSOR_ID_MAX)
        return -EINVAL;

    sensors[id]->write(sensors[id], buf, len);
}

int sensor_ioctl(int id, int cmd, void *arg)
{
    if (id > SENSOR_ID_MAX)
        return -EINVAL;

    sensors[id]->ioctl(sensors[id], cmd, arg);
}

int sensor_poll(int id, sensor_event_t *event)
{
    if (id > SENSOR_ID_MAX)
        return -EINVAL;

    sensors[id]->poll(sensors[id], event);
}
