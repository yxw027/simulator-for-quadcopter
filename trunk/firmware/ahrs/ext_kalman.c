#include "ext_kalman.h"

/**
 * @var x The state vector
 * @brief \f x \f = \left[ q0 q1 q2 q3 bp bq br \right] \n
 * where \n
 * \f [ q0 q1 q2 q3]\hat:quaternion attitude representation \n
 * \f[ bp bq br \f]:bias of rotation rate measurements \n
 */
static double x[7];

/**
 * @var z The measurement vector
 * \f z \f = \f[ q0 q1 q2 q3 \f]
 */
double z[4] = { 0 };

/**
 * @var u The input vector
 * \f u \f = \f[ p q r \f]
 */
double u[3] = {
    0.0, 0.0, 0.0
};

/* transition matrix */
double A[7][7] = {
    { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 },
    { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 },
    { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 },
    { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 },
    { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 }
};

/* observation matrix */
double H[4][7] = {
    { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 },
    { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 }
};

/* estimate error covariance matrix */
double P[7][7] = {
    { 0.0, 0.0, 0.0, 0.0 },
    { 0.0, 0.0, 0.0, 0.0 },
    { 0.0, 0.0, 0.0, 0.0 },
    { 0.0, 0.0, 0.0, 0.0 },
    { 0.1, 0.0, 0.0, 0.0 },
    { 0.1, 0.0, 0.0, 0.0 },
    { 0.1, 0.0, 0.0, 0.0 },
};

/* kalman gian */
double K[7][3];

/* process noise matrix */
double W[7][7];

/* process noise covariance matrix */
double Q[7][7] = { 0 };

/* measurement noise */
double v[3];

/* measurement noise covariance matrix */
double R[3][3];

/* angle error */
double err[3][1];

void ext_kalman_initial(ext_kalman_t *this)
{
    euler2quat(psi, theta, phi, double quat[]);
    /* initial estimate and bias */
    {
        x[0] = quat[0];
        x[1] = quat[1];
        x[2] = quat[2];
        x[3] = quat[3];
        x[4] = ;
        x[5] = ;
        x[6] = ;
    }
    P[77];

    R[0][0] = 0.01;
    R[1][1] = 0.01;
    R[2][2] = 0.01;

    W[0][0] = process_quaternion_convariance;
    W[1][1] = process_quaternion_convariance;
    W[2][2] = process_quaternion_convariance;
    W[3][3] = process_quaternion_convariance;
    W[4][4] = process_bias_convariance;
    W[5][5] = process_bias_convariance;
    W[6][6] = process_bias_convariance;
}

void ext_kalman_predict(ext_kalman_t *this)
{
    /* Project the state ahead */
    propagate_state(gyro, dt);
    /* Project the error covariance ahead */
    propagate_covariance();
}

void ext_kalman_correct(ext_kalman_t *this)
{
    /* Innovation or measurement residual */
    angle_err[0][0] = ;
    angle_err[0][0] = ;
    angle_err[0][0] = ;    
    /* Innovation (or residual) covariance */
    /* Compute the Kalman gian */
    /* Update the error covariance */
        double W[3];/*omiga*/
    /* 25ms routine */
    W[0] = u[0] - x[4];
    W[1] = u[1] - x[5];
    W[2] = u[2] - x[6];
    make_A(W, dt);
        a_measured[0] = accel_read_x();
    a_measured[1] = accel_read_y();
    a_measured[2] = accel_read_z();
    /* 3-axis dynamic acceleration can be obtained from GPS receiver */
    a_dynamic[] = 
    /* Correct body acceleration for centrifugal effect */
    WV = vector_crossproduct(W, V);
    [1] += W[2] * d_buff1 ;      
      V_buff[2] -= W[1] * d_buff1 ;
    
}

void make_A(double gyros[3], double dt)
{
    double pdot[4];
    double p, q, r;

    memset(A, 0, sizeof(A));

    p = gyros[0];
    q = gyros[1];
    r = gyros[2];

    pdot[0] = x[0] * dt / 2;
    pdot[1] = x[1] * dt / 2;
    pdot[2] = x[2] * dt / 2;
    pdot[3] = x[3] * dt / 2;

    A[0][0] = 1.0;
    A[0][1] = -p;
    A[0][2] = -q;
    A[0][3] = -r;
    A[0][4] = q1 * dt / 2;
    A[0][5] = q2 * dt / 2;
    A[0][6] = q3 * dt / 2;

    A[1][0] = p;
    A[1][1] = 1.0;
    A[1][2] = r;
    A[1][3] = -q;
    A[1][4] = -q0 * dt / 2;
    A[1][5] = q3 * dt / 2;
    A[1][6] = -q2 * dt / 2;

    A[2][0] = q;
    A[2][1] = -r;
    A[2][2] = 1.0;
    A[2][3] = p;
    A[2][4] = -q3 * dt / 2;
    A[2][5] = -q0 * dt / 2;
    A[2][6] = q1 * dt / 2;

    A[3][0] = r;
    A[3][1] = q;
    A[3][2] = -p;
    A[3][3] = 1.0;
    A[3][4] = q2 * dt / 2;
    A[3][5] = -q1 * dt / 2;
    A[3][6] = -q0 * dt / 2;

    A[4][4] = 1.0;
    A[5][5] = 1.0;
    A[6][6] = 1.0;
#ifdef AHRS_DEBUG
    matrix_t matrix = matrix_get(A);
    matrix_print(matrix);
#endif
}

void make_H()
{
    H[0][0] = 1.0;
    H[1][1] = 1.0;
    H[2][2] = 1.0;
    H[3][3] = 1.0;
}

void make_DCM()
{
}

/**
 * @brief Propagate quaternion
 * @param gx x-axis gyro data, including bias
 * @param gy y-axis gyro data, including bias
 * @param gz y-axis gyro data, including bias 
 * @param dt Delta between updates
 * @return None
 */
void propagate_state(double u[3], double dt)
{
    int i;
    double mag = 0.0;
    double q[4];
    double pqr[3];

    for (i = 0; i < 4; i++)
        q[i] = x[i];
/*
    x[0] = A[0][0] * q[0] + A[0][1] * q[1] + A[0][2] * q[2] + A[0][3] * q[3];
    x[1] = A[1][0] * q[0] + A[1][1] * q[1] + A[1][2] * q[2] + A[1][3] * q[3];
    x[2] = A[2][0] * q[0] + A[2][1] * q[1] + A[2][2] * q[2] + A[2][3] * q[3];
    x[3] = A[3][0] * q[0] + A[3][1] * q[1] + A[3][2] * q[2] + A[3][3] * q[3];
*/
    pqr[0] = u[0] - x[4];
    pqr[1] = u[1] - x[5];
    pqr[2] = u[2] - x[6];
    /* new quaternion estimate */
    x[0] += (-q[1] * pqr[0] - q[2] * pqr[1] - q[3] * pqr[2]) * dt / 2;
    x[1] += (q[0] * pqr[0] - q[3] * pqr[1] + q[2] * pqr[2]) * dt / 2;
    x[2] += (q[3] * pqr[0] + q[0] * pqr[1] - q[1] * pqr[2]) * dt / 2;
    x[3] += (q[2] * pqr[0] + q[1] * pqr[1] + q[0] * pqr[2]) * dt / 2;

    /* normalize */
    //normalize(x, 4);

    /* bias estimate */
    x[4]
    x[5]
    x[6]
}

/**
 * @brief Propagate state covariance
 */
void propagate_covariance()
{
    double AT[49];
    double AP[49];

    matrix_t a = matrix_get(A);
    matrix_t at = matrix_get(AT);
    matrix_t ap = matrix_get(AP);
    matrix p = matrix_get(P);

    matrix_transpose(at, a);

    matrix_mult(ap, a, p);
    matrix_mult(p, ap, at);
    matrix_add(p, p, w);
}