/**
 * @file ahrs.c
 * @brief The AHRS implementation
 */

#include "ahrs.h"

/**
 * N is the number of element in state vector
 */
#define N   7

/**
 * M is the number of measure
 */
#define M   3

/**
 * NW is the number of process noise random varibles
 */
#define NW  

/**
 * NV is the number of measure noise random variables
 */
#define NV

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
 * \end{array} \right ] = \frac{1}{2} \Omega \cdot q = \frac{1}{2}
 * \left [ \begin{array}{ccccccc}
 * 0 & -p & -q & -r & 0 & 0 & 0 \\ \\
 * p & 0 & r & -q & 0 & 0 & 0 \\ \\
 * q & -r & 0 & p & 0 & 0 & 0 \\ \\
 * r & q & -p & 0 & 0 & 0 & 0 
 * \end{array} \right ]
 * \left [ \begin{array}{c}
 * q0 \\ \\ q1 \\ \\ q2 \\ \\ q3 \\ \\ 0 \\ \\ 0 \\ \\ 0
 * \end{array} \right ] = \frac{1}{2} \cdot
 * \left [ \begin{array}{c}
 * -p \cdot q1 - q \cdot q2 - r \cdot q3 \\ \\
 * p  \cdot q0 + r  \cdot q2 - q  \cdot q3 \\ \\
 * q \cdot q0 - r \cdot q1 + p \cdot q3 \\ \\
 * r \cdot q0 + q \cdot q1 - p \cdot q2 \\ \\
 * 0 \\ \\
 * 0 \\ \\
 * 0 
 * \end{array} \right ] \f]
 * where \f[ {\left [ \begin{array}{cccc}
 * q0 & q1 & q2 & q3
 * \end{array} \right ]}^T \f]
 * is the quaternion and
 * \f[ {\left [ \begin{array}{ccc}
 * bp & bq & br
 * \end{array} \right ]}^T \f]
 * is the gyroscope bais.
 */
double x[N];

/**
 * @a z is the measure vector
 * \f[ z = \left [ \begin{array}{c} \phi \\ \\ \theta \\ \\ \psi \end{array} \right ] =
 * \left [ \begin{array}{c}
 * atan(\frac{2(q2q3+q0q1)}{1-2(q1^2+q2^2)}) \\ \\ -asin(2(q1q3-q0q2)) \\ \\ atan(\frac{2(q1q2+q0q3)}{1-2(q2^2+q3^2)})
 * \end{array} \right ] \f]
 * where \f$ \phi \f$ is roll angle  \n
 * \f$ \theta \f$ is pitch angle \n
 * \f$ \psi \f$ is yaw angle
 */
double z[M];

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
double A[N][N];
static void make_A(double u[3])
{
    double q0 = x[0];
    double q1 = x[1];
    double q2 = x[2];
    double q3 = x[3];

    double p = u[0] - x[4];
    double q = u[1] - x[5];
    double r = u[2] - x[6];

    A[0][0] = 0;
    A[0][1] = -p / 2;
    A[0][2] = -q / 2;
    A[0][3] = -r / 2;
    A[0][4] = q1 / 2;
    A[0][5] = q2 / 2;
    A[0][6] = q3 / 2;

    A[1][0] = p / 2;
    A[1][1] = 0;
    A[1][2] = r / 2;
    A[1][3] = -q / 2;
    A[1][4] = -q0 / 2;
    A[1][5] = q3 / 2;
    A[1][6] = -q2 / 2;

    A[2][0] = q / 2;
    A[2][1] = -r / 2;
    A[2][2] = 0;
    A[2][3] = p / 2;
    A[2][4] = -q3 / 2;
    A[2][5] = -q0 / 2;
    A[2][6] = q1 / 2;

    A[3][0] = r / 2;
    A[3][1] = q / 2;
    A[3][2] = -p / 2;
    A[3][3] = 0;
    A[3][4] = q2 / 2;
    A[3][5] = -q1 / 2;
    A[3][6] = -q0 / 2;

    A[4][0] = 0;
    A[4][1] = 0;
    A[4][2] = 0;
    A[4][3] = 0;
    A[4][4] = 0;
    A[4][5] = 0;
    A[4][6] = 0;

    A[5][0] = 0;
    A[5][1] = 0;
    A[5][2] = 0;
    A[5][3] = 0;
    A[5][4] = 0;
    A[5][5] = 0;
    A[5][6] = 0;

    A[6][0] = 0;
    A[6][1] = 0;
    A[6][2] = 0;
    A[6][3] = 0;
    A[6][4] = 0;
    A[6][5] = 0;
    A[6][6] = 0;
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

static void stateEq(float u[3], float x[4], float xdot[4])
{
    float p = u[0];
    float q = u[1];
    float r = u[2];

    float q0 = x[0];
    float q1 = x[1];
    float q2 = x[2];
    float q3 = x[3];

    xdot[0] = (-p * q1 - q * q2 - r * q3) / 2;
    xdot[1] = (p * q0 - q * q3 + r * q2) / 2;
    xdot[2] = (p * q3 + q * q0 - r * q1) / 2;
    xdot[3] = (-p * q2 + q * q1 + r * q0) / 2;
}

static void rk4(float u[3][3], float x[4], float xdot[4], float h)
{
    int i;
    float k1[4], k2[4], k3[4], k4[4];
    float y0[4], y1[4], y2[4], y3[4];
    float y[4];

    for (i = 0; i < 4; i++)
        y0[i] = x[i];
    stateEq(u[0][0], y0, k1);

    for (i = 0; i < 4; i++)
        y1[i] = y0[i] + 1 / 2 * h * k1[i];
    sateEq(u[1][0], y1, k2);

    for (i = 0; i < 4; i++)
        y2[i] = y0[i] + 1 / 2 * h * k2[i];
    stateEq(u[1][0], y2, k3);

    for (i = 0; i < 4; i++)
        y3[i] = y0[i] + h * k3[i];
    stateEq(u[2][0], y3, k4);

    for (i = 0; i < 4; i++) {
        y[i] = y0[i] + 1 / 6 * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) * h;
        xdot[i] = y[i];
    }
}

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

static void calculate_P()
{
    int i, j, k;
    double AT[49];
    double AP[49];
    for (i = 0; i < N; i++) {
        for (j = i; j < N; j++) {
        }
    }
    matrix_t a = matrix_get(A);
    matrix_t at = matrix_get(AT);
    matrix_t ap = matrix_get(AP);
    matrix p = matrix_get(P);

    matrix_transpose(at, a);

    matrix_mult(ap, a, p);
    matrix_mult(p, ap, at);
    matrix_add(p, p, w);
}

void ahrs_predict(double u[3], double dt)
{
    make_process(u, dt);
    make_A(u);
    calculate_P();
}

void ahrs_correct(double z[3])
{
    int i;
    double dz[3][1];
    matrix mk = matrix_get(K);
    matrix mdz = matrix_get(dz);
    matrix mxdot = matrix_get(Xdot);

    matrix_mult(mxdot, mk, mdz);
    matrix_add(mx, mx, mxdot);
}

void ahrs_update()
{

    /* high update rate, 50Hz */
    ext_kalman_predict();

    /* low update rate, 4Hz */
    ext_kalman_correct();
}