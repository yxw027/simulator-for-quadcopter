/**
 * @file math.h
 * @brief math interface
 */
#ifndef _MATH_H
#define _MATH_H

#include <math.h>

#include "quaternion.h"

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @defgroup math
 * @{
 */

/**
 * @def M_PI
 * PI value
 */
#define M_PI    3.1415926

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



// #define LIMIT(min, val, max)   do {} while (0)

/** @} */

/** @} */

#endif /* _MATH_H */