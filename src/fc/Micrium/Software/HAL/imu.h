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
        double x;
        double y;
        double z;
        double val[3];
        double gps[16];
    };
};

#define SENSOR_ID_ACCEL     0
#define SENSOR_ID_GYRO      1
#define SENSOR_ID_MAG       2
#define SENSOR_ID_GPS       4

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
int IMU_Update(struct event *event);

/** @} */

/** @} */

#endif /* _IMU_H */
