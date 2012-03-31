/**
 * @file imu.h
 * @brief IMU module interface
 */

#ifndef _IMU_H
#define _IMU_H

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup HAL
 * @{
 */

struct event {
    int id;
    int axis;
    union {
        double x, y, z;
    } val;
    union double x;
    union double y;
    union double z;
};

#define ID_ACCEL    0
#define ID_GYRO     1
#define ID_MAG      2

#define AXIS_X      0
#define AXIS_Y      1
#define AXIS_Z      2
#define AXIS_ALL    3

/**
 * @brief Update sensors data
 *
 * @param event The pointer to structrue
 * @return 0 success, otherwise negative error
 */
int imu_update(struct event *event);

/** @} */

/** @} */

#endif /* _IMU_H */
