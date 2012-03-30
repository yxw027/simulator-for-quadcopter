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
    double *K;  /**< kalman gain */
    void (*make_A)(struct ekf *filter);
    void (*make_H)(struct ekf *filter);
    void (*make_process)(struct ekf *filter, double u[], double dt);
    void (*make_measure)(struct ekf *filter, double z[]);
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
 * @param filter The ekf 
 * @param u The input vector
 * @param dt The timeval between prediction
 * @return None
 */ 
void ekf_predict(struct ekf *filter, double u[], double dt);

/**
 * measurement function
 *
 * @param filter The ekf
 * @param z The measure vector
 * @return None
 */
void ekf_correct(struct ekf *filter, double z[]);

/**
 * @brief Get state vector
 *
 * @param filter The ekf
 * @param X The vector to be filled
 * @return None
 */
void ekf_get_state(struct ekf *filter, double X[]);

#endif /* _EKF_H */
