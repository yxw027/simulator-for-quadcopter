/**
 * @file ekf.h
 * @brief The Extended Kalman Filter interface
 */

#ifndef _EKF_H
#define _EKF_H

struct ekf {
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

struct ekf *ekf_new()
#define DECLARE_EKF(name)  \
    struct ekf name;
    name.X = X;
    name.P = P;
    name.Q = Q;
    name.R = R;
    name.F = F;
    name.H = H;
    name.E = E;
    name.K = K;

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
 * @param measure The measurement
 *
 * @return None
 */
void ekf_correct(struct ekf *filter, double measure[3]);

void ekf_get_state(struct ekf *filter, double X[]);

#endif /* _EKF_H */
