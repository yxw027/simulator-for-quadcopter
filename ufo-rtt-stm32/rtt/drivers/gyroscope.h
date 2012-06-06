#define L3G4200D    0

#ifndef SENSOR_GYROSCOPE
  #define SENSOR_GYROSCOPE    L3G4200D
#else
  #warning "No gyroscope defined"
#endif

#if SENSOR_GYROSCOPE == L3G4200D
#define SPI_WRITE       (0x0 << 7)
#define SPI_READ        (0x1 << 7)

#define SPI_M           (0x1 << 6)
#define SPI_S           (0x0 << 0)
#endif

extern void gyro_init(void);

/**
 * @brief Read byte from given register
 *
 * @param reg The register read from
 * @param data The pointer to the data
 * @return 0 success, negative error
 */
u8 l3g4200d_read(u8 reg, u8 *data);

/**
 * @brief Write data to given register
 *
 * @param reg The register write to
 * @param data The data to be written
 * @return 0 success, negative error
 */
u8 l3g4200d_write(u8 reg, u8 data);
