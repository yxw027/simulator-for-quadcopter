#ifndef _IACCELEROMETER_H
#define _IACCELEROMETER_H
/**
 * @file IAccelerometer.h
 * Accelerometer Sensor Interface.
 */

extern int flag; /** reserverd */

/**
 * Get x, y, z axis raw data
 *
 * @param x the pointer to x-axis data
 * @param y the pointer to y-axis data
 * @param z the pointer to z-axis data
 *
 * @return 0 success, negative otherwise
 */ 
int IAccelerometer_getXYZ(uint32_t *x, uint32_t *y, uint32_t *z);

/**
 * Helper function if necessary
 */
extern int getX(uint32_t *x);
extern int getY(uint32_t *y);
extern int getZ(uint32_t *z);

extern int get_offset_x(uint32_t *x);
extern int get_offset_y(uint32_t *y);
extern int get_offset_z(uint32_t *z);

typedef struct accl_event_t {
    uint32_t x;
    uint32_t y;
    uint32_t z;
} accl_sensor_t;

/**
 * accelerometor bias varible for accelerometer calibration
 *
 * offset_x for x-axis
 * offset_y for y-axis
 * offset_z for z-axis
 *
 * @note Not threadsafe
 */    
typedef struct accl_offset_t {
    uint32_t offset_x;
    uint32_t offset_y;
    uint32_t offset_z;
} accel_offset_t;

typedef struct accl_sensor_t {
    struct accl_event_t value;
    struct accl_offset_t offset;
} accl_sensor_t;
    
int accl_get_offset(struct accel_offset *offset)
{
    get_offset_x(offset->offset_x);
    get_offset_y(offset->offset_y);
    get_offset_z(offset->offset_z);
}

int accl_update_offset(struct accel_offset *offset);


#endif /* _IACCELEROMETER_H */