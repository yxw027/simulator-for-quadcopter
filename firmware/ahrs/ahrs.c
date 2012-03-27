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
 * \f[ A_{[i,j]} = \frac{\partial f_{[i]}}{\partial x_{[j]}} = 1/2 *
 * \left [ \begin{array}{ccccccc}
 * 0 & -p & -q & -r & q1 & q2 & q3 \\ \\
 * p & 0 & r & -q & -q0 & q3 & -q2 \\ \\
 * q & -r & 0 & p & -q3 & -q0 & q1 \\ \\
 * r & q & -p & 0 & q2 & -q1 & -q0 \\ \\
 * 0 & 0 & 0 & 0 & 0 & 0 & 0 \\ \\
 * 0 & 0 & 0 & 0 & 0 & 0 & 0 \\ \\
 * 0 & 0 & 0 & 0 & 0 & 0 & 0 
 * \end{array} \right ] \f]
 */
double A[7][7];
static void make_A(double u[3])
{
    double q0 = x[0];
    double q1 = x[1];
    double q2 = x[2];
    double q3 = x[3];

    double p = u[0] - x[4];
    double q = u[1] - x[5];
    double r = u[2] - x[6];

    double arrary[7][7] = {
        { 0, -p, -q, -r,  q1,  q2,  q3 },
        { p,  0,  r, -q, -q0,  q3, -q2 },
        { q, -r,  0,  p, -q3, -q0,  q1 },
        { r,  q, -p,  0,  q2, -q1, -q0 },
        { 0,  0,  0,  0,   0,   0,  0  },
        { 0,  0,  0,  0,   0,   0,  0  },
        { 0,  0,  0,  0,   0,   0,  0  },
    };

    memcpy(A, array, sizeof(arrary));
}

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
double DCM[3][3];
static void make_DCM()
{
    double q0 = x[0];
    double q1 = x[1];
    double q2 = x[2];
    double q3 = x[3];

    DCM[0][0] = 1 - 2 * (q2 * q2 + q3 * q3);
    DCM[0][1] = 2 * (q1 * q2 + q0 * q3);
    DCM[0][2] = 2 * (q1 * q3 - q0 * q2);
    DCM[1][0] = 2 * (q1 * q2 - q0 * q3);
    DCM[1][1] = 1 - 2 * (q1 * q1 + q3 * q3);
    DCM[1][2] = 2 * (q2 * q3 + q0 * q1);
    DCM[2][0] = 2 * (q1 * q3 + q0 * q2);
    DCM[2][1] = 2 * (q2 * q3 - q0 * q1);
    DCM[2][2] = 1 - 2 * (q1 * q1 + q2 * q2);
}

static void make_H();
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

/**
 * New quaternion estimate
 *
 * \f[ \left [ \begin{arrary}{c} x_0 x_1 x_2 x_3 x_4 x_5 x_6 \end{array} \right ] = 1/2 *
 * \left [ \begin{array}{c}
 * -p * x_1 - q * x_2 - r * x_3 \\ \\
 * p * x_0 + r * x_2 - q * x_3 \\ \\
 * q * x_0 - r * x_1 + p * x_3 \\ \\
 * r * x_0 + q * x_1 - p * x_2 \\ \\
 * 0 \\ \\
 * 0 \\ \\
 * 0
 * \end{array} \right ] \f]
 */
static void make_process(double u[3], double dt)
{
    double xdot[7];

    double p = u[0] - x[4];
    double q = u[1] - x[5];
    double r = u[2] - x[6];

    double q0 = x[0];
    double q1 = x[1];
    double q2 = x[2];
    double q3 = x[3];

    xdot[0] = (-p * q1 - q * q2 - r * q3) * dt / 2;
    xdot[1] = (p * q0 - q * q3 + r * q2) * dt / 2;
    xdot[2] = (p * q3 + q * q0 - r * q1) * dt / 2;
    xdot[3] = (-p * q2 + q * q1 + r * q0) * dt / 2;
    xdot[4] = 0;
    xdot[5] = 0;
    xdot[6] = 0;

#ifdef AHRS_DEBUG
#endif
}

static void make_measure()
{
    double q0 = x[0];
    double q1 = x[1];
    double q2 = x[2];
    double q3 = x[3];

    z[0] = atan2(2 * (q2 * q3 + q0 * q1), 1 - 2 * (q1 * q1 + q2 * q2));
    z[1] = -asin(2 * (q1 * q3 - q0 * q2));
    z[2] = atan2(2 * (q1 * q2 + q0 * q3), 1 - 2 * (q2 * q2 + q3 * q3));
}

void ahrs_init()
{
    init_IMU();
    ext_kalman_initial();
}

void ahrs_predict(double u[3], double dt)
{
    make_process(u, dt);
    make_A(u);
    make_P();
}

void ahrs_correct(double z[3])
{
}

void ahrs_update()
{

    /* high update rate, 50Hz */
    ext_kalman_predict();

    /* low update rate, 4Hz */
    ext_kalman_correct();
}