/**
 * @file ahrs.c
 * @brief The AHRS implementation
 */

/**
 * @a x is the state vector, and defined as follows:\n
 * \f[ x = \left [ \begin{array}{c}
 * q0 \\ \\
 * q1 \\ \\
 * q2 \\ \\
 * q3 \\ \\
 * bp \\ \\
 * bq \\ \\
 * br
 * \end{array} \right ] =
 * \left [ \begin{array}{c}
 * x_{k-1} + TODO
 * \end{array} \right ] \f]
 * where \f[ \left [ \begin{array}{c}
 * q0 \\ \\
 * q1 \\ \\
 * q2 \\ \\
 * q3
 * \end{array} \right ] \f]
 * is the quaternion and
 * \f[ \left [ \begin{array}{c}
 * bp \\ \\
 * bq \\ \\
 * br
 * \end{array} \right ] \f]
 * is the gyroscope bais.
 */
double x[7];

/**
 * @a z is the measure vector \n
 * \f[ z = \left [ \begin{array}{c} \phi \\ \\ \theta \\ \\ \psi \end{array} \right ] =
 * left [ \begin{array}{c}
 * atan(\frac{2(q2q3+q0q1)}{1-2(q1^2+q2^2)}) \\ \\ -asin(2(q1q3-q0q2)) \\ \\ atan(\frac{2(q1q2+q0q3)}{1-2(q2^2+q3^2)})
 * \end{array} \right ] \f]
 * where \f$ \phi \f$ is roll angle  \n
 * \f$ \theta \f$ is pitch angle \n
 * \f$ \psi \f$ is yaw angle
 */
double z[3];

/**
 * input vector
 * \f[ u = \left [ \begin{array}{c}
 * p \\ \\
 * q \\ \\
 * q
 * \end{array} \right ] \f]
 */
double u[3];

/**
 * A is an \a n by \a n jacobian matrix of partial derivatives,
 * defined as follow :
 * \f[
 * A_{[i,j]} = \frac{\partial f_{[i]}}{\partial x_{[j]}} =
 * \left [ \begin{array}{ccccccc}
 * \end{array} \right ]
 * \f]
 */
double A[7][7];

/**
 * H is an \a m by \a n jacobian matrix of partial derivatives,
 * defined as follow :
 * \f[
 * H_{[i,j]} = \frac{\partial h_{[i]}}{\partial x_{[j]}} =
 * \left [ \begin{array}{ccccccc}
 * \end{array} \right ]
 * \f]
 */
double H[3][7];

double P[7][7];
/* kalman gian */
double K[7][3];
/* process noise matrix */
double W[7][7];
/* process noise covariance matrix */
double Q[7][7];
/* measurement noise covariance matrix */
double R[3][3];
double V[3][3];

void ahrs_init()
{
    init_IMU();
    ext_kalman_initial();
}

void ahrs_update()
{

    /* high update rate, 50Hz */
    ext_kalman_predict();

    /* low update rate, 4Hz */
    ext_kalman_correct();
}