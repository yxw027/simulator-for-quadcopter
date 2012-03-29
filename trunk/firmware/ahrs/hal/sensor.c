#include "sensor.h"
#include "errno.h"

extern devices[];

int sensor_read(int id, char *buf, int len)
{
	if (id > SENSOR_ID_MAX)
		return -EINVAL;
	devices[id]->read(buf, len);
}

int sensor_write(int id, char *buf, int len)
{
	if (id > SENSOR_ID_MAX)
		return -EINVAL;
    devices[id]->write(buf, len);
}

int sensor_ioctl(int id, int cmd, void *arg)
{
	if (id > SENSOR_ID_MAX)
		return -EINVAL;
    devices[id]->ioctl(cmd, arg);
}