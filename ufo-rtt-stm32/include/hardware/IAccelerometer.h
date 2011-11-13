/**
 * @file IAccelerometer.h
 * Accelerometer Sensor Interface.
 */

#ifndef _IACCELEROMETER_H
#define _IACCELEROMETER_H

/**
 * @addtogroup ufo
 * @}
 */

/**
 * @addtogroup Hardware Abstract Layer
 * @{
 */

extern int flag; /** reserverd */

/**
 * Get accelerometer raw data
 *
 * @param pointer to event
 *
 * @return 0 success, negative otherwise
 */
int accl_get_value(struct accl_event_t *event);

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
    uint32_t ax;
    uint32_t ay;
    uint32_t az;
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
    uint32_t accl_offset_x;
    uint32_t accl_offset_y;
    uint32_t accl_offset_z;
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

/**
 * initialize accelerometor
 *
 * @return none
 */
void init_hw_accl(); 

/**
 * get raw data of x, y, z axis
 *
 * @param value the pointer to value
 * @return 0 success, negetive otherwise
 */
int accl_get_value(struct accl_event_t *value);

int accl_update_offset(struct accel_offset *offset);

/** @} */

/** @} */

#endif /* _IACCELEROMETER_H */