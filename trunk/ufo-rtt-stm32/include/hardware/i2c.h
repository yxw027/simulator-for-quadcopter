/**
 * @file i2c.h
 * i2c interface
 */
#ifndef _I2C_H
#define _I2C_H

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup Hardware Abstract Layer
 * @{
 */

/**
 * @defgroup i2c
 * I2C bus support
 * @{
 */

typedef struct i2c_dev_t {
    char *name;
    int addr;
} i2c_dev_t ;
    
int i2c_probe(uint16_t addr);
int i2c_read();
int i2c_write();

/** @} */

/** @} */

/** @} */

#endif /* _I2C_H */
