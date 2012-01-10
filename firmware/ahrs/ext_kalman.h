typedef struct ext_kalman_t {
    double A[3][4]; /**< State estimation matrix. */
    double P[2][2]; /**< Covariance of estimation error matrix. */
    double X[7];    /**< \f x = \left[ q0 q1 q2 q3 bp bq br \right] \hat \f */
    void *data;     /**< Private data */
} ext_kalman_t;