#include "ext_kalman.h"

/* state vector */
double x[7];

double z[4] = { 0 };

double u[3][3] = {
    { 0.0, 0.0, 0.0 },  /* p q r */
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

double Q[7][7] = { 0 };

/* kalman gian */
double K[7][3];

/* process noise matrix */
double W[7][7];

/* measurement noise matrix */
double R[3][3];

/* angle error */
double angle_err[3][1];

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
}

void ext_kalman_predict(ext_kalman_t *this)
{
    /* Project the state ahead */
    propagate_state();
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

void make_A(double dt)
{
    double pdot[4];

    memset(A, 0, sizeof(A));

    pdot[0] = x[0] * dt / 2;
    pdot[1] = x[1] * dt / 2;
    pdot[2] = x[2] * dt / 2;
    pdot[3] = x[3] * dt / 2;

    A[0][0] = 1.0;
    A[0][4] = pdot[1];
    A[0][5] = pdot[2];
    A[0][6] = pdot[3];

    A[1][1] = 1.0;
    A[1][4] = -pdot[0];
    A[1][5] = pdot[1]; //???
    A[1][6] = -pdot[2];

    A[2][2] = 1.0;
    A[2][4] = -pdot[3];
    A[2][5] = -pdot[0];
    A[2][6] = pdot[1];

    A[3][3] = 1.0;
    A[3][4] = pdot[2];
    A[3][5] = -pdot[1];
    A[3][6] = -pdot[0];

    A[4][4] = 1.0;
    A[5][5] = 1.0;
    A[6][6] = 1.0;
}

void make_H()
{
    H[0][0] = 1.0;
    H[1][1] = 1.0;
    H[2][2] = 1.0;
    H[3][3] = 1.0;
}

/**
 * @brief Propagate quaternion
 * @param gx x-axis gyro data, including bias
 * @param gy y-axis gyro data, including bias
 * @param gz y-axis gyro data, including bias 
 * @param dt Delta between updates
 * @return None
 */
void propagate_state(double gx, double gy, double gz, double dt)
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
    pqr[0] = gx - x[4];
    pqr[1] = gy - x[5];
    pqr[2] = gz - x[6];
    /* new quaternion estimate */     
    x[0] += (-q[1] * pqr[0] - q[2] * pqr[1] - q[3] * pqr[2]) * dt / 2;
    x[1] += (q[0] * pqr[0] - q[3] * pqr[1] - q[2] * pqr[2]) * dt / 2;
    x[2] += (q[3] * pqr[0] + q[0] * pqr[1] - q[1] * pqr[2]) * dt / 2;
    x[3] += (q[2] * pqr[0] + q[1] * pqr[1] + q[0] * pqr[2]) * dt / 2;

    /* normalize */
    for (i = 0; i < 4; i++)
        mag += x[i] * x[i];
    mag = sqrt(mag);
    for (i = 0; i < 4; i++)
        x[i] /= mag;

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
   double tA[49];
   double AP[49];
   double APtA[49];
   // TODO
//   P	= A*P*(A.transpose()) + W;

}