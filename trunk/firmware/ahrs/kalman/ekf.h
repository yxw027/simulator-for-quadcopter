/**
 * @file ekf.h
 * @brief The Extended Kalman Filter interface
 */

#ifndef _EKF_H
#define _EKF_H

struct ekf {
    int n;      /**< state dimension */
    int m;      /** measure dimension */
    double *X;  /**< state vector */
    double *P;  /**< state covariance matrix */
    double *Q;  /**< process covariance noise */
    double *R;  /**< measurement convariance noise */
    double *A;  /**< jacobian of Xdot wrt X */
    double *H;  /**< jacobian of measure wrt X */
    double *E;  /**< error matrix */
    double *K;  /**< kalman gain */
    void (*make_A)(void);
    void (*make_H)(void);
    void (*make_process)(double *u, double *, double dt);
    void (*make_measure)(double *, double *, double *);
};

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
void ekf_init(struct ekf *filter, int n, int m, double *Q, double *R);

/**
 * time update function
 *
 * @param filter The pointer 
 * @param u The input vector
 * @param dt The timeval between prediction
 *
 * @return None
 */ 
void ekf_predict(struct ekf *filter, double u[], double dt);

/**
 * measurement function
 *
 * @param filter
 * @param measure The measure vector
 *
 * @return None
 */
void ekf_correct(struct ekf *filter, double measure[3]);

void ekf_get_state(struct ekf *filter, double X[]);

#endif /* _EKF_H */
