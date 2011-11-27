/**
 * @file accel.h
 * @brief Accelerometer Sensor Interface.
 */

#ifndef _ACCEL_H
#define _ACCEL_H

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup HAL
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
int accel_get_value(struct accel_event_t *event);

/**
 * Helper function if necessary
 */
extern int getX(uint32_t *x);
extern int getY(uint32_t *y);
extern int getZ(uint32_t *z);

extern int get_offset_x(uint32_t *x);
extern int get_offset_y(uint32_t *y);
extern int get_offset_z(uint32_t *z);

typedef struct accel_event_t {
    uint32_t x;     /**< x-axis value of accelerometer */
    uint32_t y;     /**< y-axis value of accelerometer */
    uint32_t z;     /**< z-axis value of accelerometer */
} accel_event_t;

/**
 * accelerometor bias varible for accelerometer calibration
 *
 * offset_x for x-axis
 * offset_y for y-axis
 * offset_z for z-axis
 *
 * @note Not threadsafe
 */    
typedef struct accel_offset_t {
    uint32_t a_offset_x;
    uint32_t a_offset_y;
    uint32_t a_offset_z;
} accel_offset_t;

typedef struct accel_sensor_t {
    struct accel_event_t value;
    struct accel_offset_t offset;
} accel_sensor_t;

int accel_get_offset(struct accel_offset *offset)
{
    get_offset_x(offset->offset_x);
    get_offset_y(offset->offset_y);
    get_offset_z(offset->offset_z);
}

/**
 * Initialize accelerometor
 *
 * @return none
 */
void accel_hw_init(); 

/**
 * Get raw data of x, y, z axis
 *
 * @param value the pointer to value
 * @return 0 success, negetive otherwise
 */
int accel_get_value(struct accel_event_t *value);

int accel_update_offset(struct accel_offset *offset);

/** @} */

/** @} */

#endif /* _ACCEL_H */