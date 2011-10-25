/**
 * @file IAccelerometer.h
 * Accelerometer Sensor Interface.
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
int IAccelerometer_getXYZ(u32 *x, u32 *y, u32 *z);

/**
 * Helper function if necessary
 */
int getX(u32 *x);
int getY(u32 *y);
int getZ(u32 *z);