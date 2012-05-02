/**
 * @file ekf.h
 * @brief The Extended Kalman Filter interface
 */

#ifndef _EKF_H
#define _EKF_H

/**
 * @addtogroup kalman
 * @{
 */

struct ekf {
    double *X;  /**< Corrected state vector */
    double *P;  /**< state covariance matrix */
    double *A;  /**< A jacobian matrix */
    double *H;  /**< A jacobian matrix */
    double *V;  /**< A jacobian matrix */
    double *R;  /**< Measurement noise convariance matrix */
    double *W;  /**< A jacobian matrix */
    double *Q;  /**< Process noise covariance matrix */
    double *E;  /**< error matrix */
    double *K;  /**< kalman gain */

    int n;      /**< Size of the state vector */
    int m;      /** Size of the measurement vector */
    int nw;     /**< process noise random variables */
    int nv;     /**< Size of the measurement noise vector */
    
    void (*make_A)(void);
    void (*make_H)(void);
    void (*make_V)();
    void (*make_R)();
    void (*make_W)();
    void (*make_Q)();
    void (*make_process)(double *u, double *, double dt);
    void (*make_measure)(double *, double *, double *);
    void (*callback)(struct ekf *ekf);

    void *data; /**< user data */
};

/**
 * @brief EKF Constructor
 *
 * @param n The number of element in state vector
 * @param m The number of measure
 * @return The pointer to the EKF
 */
struct ekf *ekf_new(int n, int m);

/**
 * @brief Initialize extended kalman filter
 *
 * @param filter The ekf to be initialized
 * @param n The number of element in state vector
 * @param m The number of element in measure vector
 * @param Q The initial Q
 * @param R The inital R
 * @return None
 */
void ekf_init(struct ekf *filter, double *Q, double *R);

/**
 * @brief time update function
 *
 * @param filter The pointer 
 * @param u The input vector
 * @param dt The timeval between prediction
 *
 * @return None
 */ 
void ekf_predict(struct ekf *filter, double u[], double dt);

/**
 * @brief measurement function
 *
 * @param filter
 * @param measure The measure vector
 *
 * @return None
 */
void ekf_correct(struct ekf *filter, double measure[3]);

void ekf_get_state(struct ekf *filter, double state[]);
void *ekf_get_data(struct ekf *filter);
void ekf_set_data(struct ekf *filter, void *data);

/** @} */

#endif /* _EKF_H */
