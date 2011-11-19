/**
 * @file quaternion.h
 * Quaternoin math library interface
 */

#ifndef _QUATERNION_H
#define _QUATERNION_H

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup math
 * @{
 */

/**
 * @defgroup quaternion
 * quaternion math support
 * @{
 */

struct euler_t;

/**
 * Quaternion elements representing the estimated orientation
 */   
typedef struct quaternion_t {
    double q0;
    double q1;
    double q2;
    double q3;
} quaternion_t;  
  
/**
 * Estimated orientation quaternion elements with initial conditions.
 */
typedef struct estimated_quaternion_t {
    double SEq_1;
    double SEq_2;
    double SEq_3;
    double SEq_4;
} estimated_quaternion_t;  

/**
 * Get euler from quaternion
 *
 * @param quaternion pointer to quaternion
 * @param euler pointer to euluer
 * @return none
 */
void quaternion_to_euler(struct quaternion_t *quad, struct euler_t *euler);

/**
 * calculate quaternion from euler
   w = c1 c2 c3 - s1 s2 s3
   x = s1 s2 c3 + c1 c2 s3
   y = s1 c2 c3 + c1 s2 s3
   z = c1 s2 c3 - s1 c2 s3

   where:
        c1 = cos(heading / 2)
        c2 = cos(attitude / 2)
        c3 = cos(bank / 2)
        s1 = sin(heading / 2)
        s2 = sin(attitude / 2)
        s3 = sin(bank / 2) 
 * @param euler the original attitude
 * @param quad quaternion from original euler
 * @return none
 */
void quaternion_from_euler(struct euler_t *euler, struct quaternion_t *quad);

/**
 * Normalize
 * 
 * @param quaternion the pointer to quaternion
 * @return none
 */
void quaternion_norm(struct quaternion_t *quaternion);

/** @} */

/** @} */

/** @} */

#endif /* _QUATERNION_H */
