#ifndef _QUATERNION_H
#define _QUATERNION_H

/**
 * @file quaternion.h
 * Quaternoin definitions
 */

/**
 * Quaternion orientation of earth frame relative to auxiliary frame.
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

#endif /* _QUATERNION_H */