Accel_calibration(struct accel_offset *offset)
{

}

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

typedef struct accl_offset_t {
    uint32_t accl_offset_x;
    uint32_t accl_offset_y;
    uint32_t accl_offset_z;
} accl_offset_t;

typedef struct gyro_bias_t {
    uint32_t gyro_bias_x;
    uint32_t gyro_bias_y;
    uint32_t gyro_bias_z;
} gyro_bias_t;

Gyro_calibration(struct gyro_bias_t *bias)
{
    int buf_size = sizeof(gyro_buf) / 4;
    
    bias->gyro_bias_x = gyro_buf_x / buf_size;
    bias->gyro_bias_y = gyro_buf_y / buf_size;
    bias->gyro_bias_z = gyro_buf_z / buf_size;
}
    
IMU_Init()
{
    /* hardware initialization */
    Accel_init();
    Gyro_init();
    
    Accel_calibration();
    Gyro_calibration();
}

/**
 * global varible for accelerometer calibration
 *
 * gAccelOffsetX for x-axis
 * gAccelOffsetY for y-axis
 * gAccelOffsetZ for z-axis
 *
 * @note Not threadsafe
 */
u32 gAccelOffsetX = 0;
u32 gAccelOffsetY = 0;
u32 gAccelOffsetZ = 0;

int check