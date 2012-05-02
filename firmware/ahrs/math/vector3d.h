/**
 * @file vector3d.h
 * @brief 3D vector interface
 */

#ifndef _VECTOR3D_H
#define _VECTOR3D_H


/**
 * @addtogroup ufo
 * @{
 */

/**
 * @defgroup math
 * @{
 */

#define DIM     3

typedef double vector3d_t[DIM];

/**
 * u = v + w
 */
void vector3d_add(vector3d_t u, vector3d_t v, vector3d_t w);

/**
 * u = v - w
 */
void vector3d_sub(vector3d_t u, vector3d_t v, vector3d_t w);
/*
vector3d_scale();
double vector3d_dot_product(vector3d_t u, vector3d v);
void vector3d_cross_product(vector3d u, vector3d v, vector3d w);
vector3d_normalize();
vector3d_mult_matrix();
*/    
/** @} */

/** @} */

#endif /* _VECTOR3D_H */
