/**
 * @file math.h
 * @brief math interface
 */
#ifndef _MATH_H
#define _MATH_H

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
#define G   9.18
#define M_PI  3.14
// #define LIMIT(a, b)   

/**
 * Quaternion
 */
void quaternion2euler(double euler[3], double q[4]);
void quaternion_normalize(double q[4]);

/**
 * Euler
 */
void euler2quaternion(double q[4], double euler[3]);

/** @} */

/** @} */

#endif /* _MATH_H */