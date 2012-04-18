/**
 * @file math.h
 * @brief math interface
 */
#ifndef _MATH_H
#define _MATH_H

#include <math.h>

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @defgroup math
 * @{
 */


/**
 * @def toDegrees(radians)
 * Convert @a radians to @a degrees
 */
#define toDegrees(radians)  ((radians) * 180.0 / M_PI)

/**
 * @def toRadians(degrees)
 * Convert @a degrees to @a radians
 */
#define toRadians(degrees)  ((degrees) / 180.0 * M_PI)

/**
 * @def G
 * Acceleration of gravity
 */
#define G       9.18

/**
 * @def M_PI
 * PI value
 */
#define M_PI    3.14
// #define LIMIT(val, min, max)    ((val) < (min))

/**
 * @brief Convert quaternion angle to euler
 *
 * @param euler Euler vector
 * @param q Quaternion vector 
 * @return None
 */
void quaternion2euler(double euler[3], double q[4]);
void quaternion_normalize(double q[4]);

/**
 * Euler
 */
/**
 * @brief Convert euler angle to quaternion
 *
 * @param q Quaternion vector 
 * @param euler Euler vector
 * @return None
 */
void euler2quaternion(double q[4], double euler[3]);

/** @} */

/** @} */

#endif /* _MATH_H */