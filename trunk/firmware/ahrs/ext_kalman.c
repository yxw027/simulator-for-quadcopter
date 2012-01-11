#include "ext_kalman.h"


void ext_kalman_initial(ext_kalman_t *this)
{
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

void make_A()
{
    A[0][0] = 1.0;
    A[][]
}

/**
 * @brief Propagate quaternion
 */
void propagate_state()
{
    int i;
    double mag = 0.0;
    double q[4];

    for (i = 0; i < 4; i++)
        q[i] = x[i];

    x[0] = A[0][0] * q[0] + A[0][1] * q[1] + A[0][2] * q[2] + A[0][3] * q[3];
    x[1] = A[1][0] * q[0] + A[1][1] * q[1] + A[1][2] * q[2] + A[1][3] * q[3];
    x[2] = A[2][0] * q[0] + A[2][1] * q[1] + A[2][2] * q[2] + A[2][3] * q[3];
    x[3] = A[3][0] * q[0] + A[3][1] * q[1] + A[3][2] * q[2] + A[3][3] * q[3];

    for (i = 0; i < 4; i++)
        mag += x[i] * x[i];
    mag = sqrt(mag);
    for (i = 0; i < 4; i++)
        x[i] /= mag;
}

/**
 * @brief Propagate state covariance
 */
void propagate_covariance()
{
   double tA[49];
   double AP[49];
   double APtA[49];
}