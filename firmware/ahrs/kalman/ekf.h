#ifndef _EKF_H
#define _EKF_H

struct ekf {
    double *X;  /**< state vector */
    double *P;  /**< state covariance matrix */
    double *Q;  /**< process covariance noise */
    double *R;  /**< measurement convariance noise */
    double *F;  /**< jacobian of Xdot wrt X */
    double *H;  /**< jacobian of measure wrt X */
    double *E;  /**< error matrix */
    double *K;  /**< kalman gain */
    void (*make_A)(void);
    void (*make_H)(void);
    void (*make_process)(double *, double *, double *);
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

void ekf_predict(struct ekf *filter, double u[], double dt);
{
    double Pdot[7];
    filter->make_A();
    filter->make_process(u, filter->X, dt);
    P[0] += Pdot[0] * dt;
    P[1] += Pdot[1] * dt;
    P[2] += Pdot[2] * dt;
    P[3] += Pdot[3] * dt;
    P[4] += Pdot[4] * dt;
    P[5] += Pdot[5] * dt;
    P[6] += Pdot[6] * dt;
}

void ekf_correct(struct ekf *filter, double angle[3]);
{
    double euler[3];

    K =;
    quat2euler(X, euler);
    err[0] = angle[0] - euler[0];
    err[1] = angle[1] - euler[1];
    err[2] = angle[2] - euler[2];
    filter->make_H();
    filter->make_measure();
}


#endif /* _EKF_H */