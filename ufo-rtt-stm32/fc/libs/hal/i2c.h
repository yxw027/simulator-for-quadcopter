/**
 * @file i2c.h
 * @brief I2C interface
 */
#ifndef _I2C_H
#define _I2C_H

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup HAL
 * Hardware Abstract Layer
 * @{
 */

/**
 * @defgroup i2c i2c
 * I2C bus support
 * @{
 */

/**
 * Description of a i2c device
 */
typedef struct i2c_dev_t i2c_dev_t;

/**
 * @struct i2c_dev_t i2c.h
 * @brief Describe A i2c device
 */ 
struct i2c_dev_t {
    char *name; /**< name the name of the i2c device */
    int addr;   /**< addr the address of the i2c device */
};

/**
 * @brief Probe i2c device
 *
 * Mode details about i2c probe
 * @param addr The address of the slave
 * @return Return 0 if success, negetive otherwise
 * @note Some note.
 * @sa i2c_read i2c_write
 */
int i2c_probe(uint16_t addr);

/**
 * issue a single I2C message in master transmit mode
 *
 * @param addr The address of the slave
 * @param buf Data will be written to the slave
 * @param count How many bytes to write
 * @return The number of bytes written if success, negative otherwise
 * @sa i2c_read
 */
int i2c_write(uint16_t addr, const char *buf, int count);

/**
 * issue a single I2C message in master recive mode
 *
 * @param addr The address of the slave
 * @param buf Where to store data read from slave 
 * @param count How many bytes to read
 * @return The number of bytes read if success, negative otherwise
 * @sa i2c_write
 */
int i2c_read(uint16_t addr, char *buf, int count);


/** @} */

/** @} */

/** @} */

#endif /* _I2C_H */
