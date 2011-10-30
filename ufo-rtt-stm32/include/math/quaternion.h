/**
 * @file quaternion.h
 * Quaternoin math library interface
 */

#ifndef _QUATERNION_H
#define _QUATERNION_H


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
 * Get euluer from quaternion
 *
 * @param quaternion pointer to quaternion
 * @param euler pointer to euluer
 * @return none 
 */
void quaternion_to_euluer(struct quaternion_t *quaternion, struct euler_t *euler);

/**
 * Normalize
 *
 * @param quaternion the pointer to quaternion
 * @return none
 */
void quaternion_norm(struct quaternion_t *quaternion);


#endif /* _QUATERNION_H */
