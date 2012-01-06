/**
 * @file imufilter.c
 * @brief IMU filter routine, using extended kalman filter.
 */


/** double q0, q1, q2, q3, bp, bq, br */
double x[7];
double z[4] = { 0 };

/** double p q r */
double u[3][3] = { 0 };

double A[7][7] = {
    { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 },
    { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 },
    { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 },
    { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 },
    { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 }
};

double H[4][7] = {
    { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 },
    { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 }
};

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

double temprature;


double psi, theta, psi;
double ax, ay, az;

double mx, my, mz;

static ext_kalman_init(ext_kalman_t *self);
static ext_kalman_predict(ext_kalman_t *self);
static ext_kalman_correct(ext_kalman_t *self);

/**
 * Assemble A matrix
 */
static void make_A()
{
    A[0][0] = 1.0;
    A[][]
}