typedef struct ext_kalman_t {
    double x[N];
//    double u[3];
    double z[M];
    double A[N][N];
    double P[N][N];    
    double W[N][NV];
    double Q[1][1]; /* TODO */
    double H[M][N];
    double V[M][NV];
    double R[1][1]; // TODO
    void *data;
} ext_kalman_t;

void ext_kalman_initial(ext_kalman_t *this);
void ext_kalman_predict(ext_kalman_t *this);
void ext_kalman_correct(ext_kalman_t *this);

/**
 * @brief Assemble state transition matrix.
 * @param None.
 * @return None.
 */
void make_A();

/**
 * We have seven variables in our state vector, the quaternion attitude
 * estimate and three gyro bias values. The state time update equation
 * comes from the IMU gyro sensor readings:
 */
extern double X[7];

extern double q0, q1, q2, q3;

extern double pqr[3];
extern double bias[3];
extern double bp, bq, br;

extern double accel[3];
extern double accel_raw[3];

extern double gyro[3];
extern double gyro_bias[3];

extern double euler[3];
extern double roll, pitch, yaw;

extern double DCM[3][3];
