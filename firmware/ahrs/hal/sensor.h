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

inline void *get_drv_data(struct sensor_t *sensor)
{
	return sensor->priv_data;
}

inline void set_drv_data(struct sensor_t *sensor, void *data)
{
	sensor.priv_data = data;
}

#define SENSOR_INIT(sensor)	\
	do {					\
		int num = sizeof(sensor) / sizeof(sensor[0]);
		int i;
		for (i = 0; i < num; i++) {
			sensor->init(sensor, sensor->priv_data);
		}
	} while(0)
	
	
sensor_read(int id, char *buf, int len)
{
	if (id > SENSOR_ID_MAX)
		return -E;
	
}