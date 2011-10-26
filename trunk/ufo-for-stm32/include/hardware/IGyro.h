/**
 * @file IGyro.h
 * Gyroscope Sensor Interface.
 */

/**
 * Get x, y, z axis raw data
 *
 * @param x the pointer to x-axis data
 * @param y the pointer to y-axis data
 * @param z the pointer to z-axis data
 *
 * @return 0 success, negative otherwise
 */
int IGyro_getXYZ(u32 *x, u32 *y, u32 *z);
 