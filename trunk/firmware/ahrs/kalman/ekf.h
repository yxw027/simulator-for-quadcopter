/**
 * @file ekf.h
 * @brief The Extended Kalman Filter interface
 * @author gouqingsong@gmail.com
 * @version v0.0.1
 * @date 2011 - 2012
 * @copyright GNU Public License Version 3
 */

#ifndef _EKF_H
#define _EKF_H

#include "matrix.h"

/**
 * @defgroup kalman
 * @{
 */

struct ekf {
    matrix_t *X;  /**< Corrected state vector */
    matrix_t *P;  /**< State covariance matrix */
    matrix_t *A;  /**< A jacobian matrix */
    matrix_t *H;  /**< H jacobian matrix */
    matrix_t *V;  /**< Measurement noise matrix */
    matrix_t *R;  /**< Measurement noise convariance matrix */
    matrix_t *W;  /**< Process noise matrix */
    matrix_t *Q;  /**< Process noise covariance matrix */

    matrix_t *E;  /**< error matrix */
    matrix_t *K;  /**< kalman gain */

    matrix_t *Tnxm; /**< The nxm tmp matrix */
    matrix_t *Tnxn; /**< The nxn tmp matrix */
    matrix_t *Tmxm; /**< The mxm tmp matrix */

    int n;      /**< Size of the state vector */
    int m;      /**< Size of the measurement vector */
    int nw;     /**< Size of the process noise vector */
    int nv;     /**< Size of the measurement noise vector */

    void (*make_A)(struct ekf *ekf);    /**< Assemble A matrix callback */
    void (*make_H)(struct ekf *ekf);    /**< Assemble H matrix callback */
    void (*make_V)(struct ekf *ekf);    /**< Assemble V matrix callback */
    void (*make_R)(struct ekf *ekf);    /**< Assemble R matrix callback */
    void (*make_W)(struct ekf *ekf);    /**< Assemble W matrix callback */
    void (*make_Q)(struct ekf *ekf);    /**< Assemble Q matrix callback */
    void (*make_P)(struct ekf *ekf);    /**< Assemble P matrix callback */
    void (*make_process)(struct ekf *ekf);  /**< state predict callback */
    void (*make_measure)(struct ekf *ekf);  /**< measure callback */
    void (*callback)(struct ekf *ekf);      /**< user callback */

    void *data; /**< user data */
};

/**
 * @brief EKF Constructor
 * @param n The number of element in state vector
 * @param m The number of measure
 * @return The pointer to the EKF if success, NULL out of memory
 */
struct ekf *ekf_new(int n, int m, int nw, int nv);

/**
 * @brief Initialize extended kalman filter
 * @param filter The ekf to be initialized
 * @param n The number of element in state vector
 * @param m The number of element in measure vector
 * @param Q The initial Q
 * @param R The inital R
 * @return None
 */
void ekf_init(struct ekf *filter, matrix_t *Q, matrix_t *R);

/**
 * @brief time update function
 * @param filter The pointer
 * @param u The input vector
 * @param dt The timeval between prediction
 * @return None
 */
void ekf_predict(struct ekf *filter, double u[], double dt);

/**
 * @brief measurement function
 * @param filter
 * @param measure The measure vector
 * @return None
 */
void ekf_correct(struct ekf *filter, double measure[3]);

void ekf_get_state(struct ekf *filter, double state[]);

void *ekf_get_data(struct ekf *filter);

void ekf_set_data(struct ekf *filter, void *data);

/** @} */

#endif /* _EKF_H */
