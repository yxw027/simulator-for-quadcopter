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
} i2c_dev_t;

int i2c_probe(uint16_t addr);

/**
 * issue a single I2C message in master transmit mode
 *
 * @param addr The address of the slave
 * @param buf Data will be written to the slave
 * @param count How many bytes to write
 * @return The number of bytes written if success, negative otherwise
 */
int i2c_write(uint16_t addr, const char *buf, int count);

/**
 * issue a single I2C message in master recive mode
 *
 * @param addr The address of the slave
 * @param buf Where to store data read from slave 
 * @param count How many bytes to read
 * @return The number of bytes read if success, negative otherwise
 */
int i2c_read(uint16_t addr, char *buf, int count);


/** @} */

/** @} */

/** @} */

#endif /* _I2C_H */
