/**
 * @file kalman.h
 * @brief Kalman filter interface
 *
 * This file contains the code for a kalman filter, an
 * extended kalman filter, and an iterated extended kalman filter.
 */

#ifndef _KALMAN_H
#define _KALMAN_H

#include "math/matrix.h"
#include "math/vector.h"

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup kalman
 * @{
 */

/**
 * @struct kalman_t kalman.h
 * @brief Describe a Kalman filter
 */
typedef struct kalman_t {
    /* callbacks */
    void (*make_A)(struct kalman_t *kalman);
    void (*make_H)(struct kalman_t *kalman);
    void (*make_V)(struct kalman_t *kalman);
    void (*make_R)(struct kalman_t *kalman);
    void (*make_W)(struct kalman_t *kalman);
    void (*make_Q)(struct kalman_t *kalman);
    void (*make_process)(struct kalman_t *kalman);
    void (*make_measure)(struct kalman_t *kalman);
    
    void *private;
    
    /*
     * The following variable is private, DO NOT modify anyway.
     */
    matrix_t *A;    /**< A is the state transtion model which is applied to the previous stare \f$ x_{k-1} \f$ */
    matrix_t *B;    /**< B is the control-input model which is applied to the controller vector \f$ u_k \f$ */
    vector_t;
    matrix_t *P;    /**< apriori covariance matrix */
    matrix_t *R;    /**< measurement noise variance vector (R) */
    matrix_t *K;    /**< the Kalman gain matrix */
} kalman_t;

/**
 * @brief Linear Kalman Filtering
 */
/**
 * @brief In order to use the Kalman filter to estimate the internal state of a process given only a sequence\n
 * of noisy observations, one must model the process in accordance with the framework of the Kalman filter.\n
 * This means specifying the following matrices: \f$ F_k \f$ , the state transition model;\n
 * \f$ H_k \f$ , the observation model; \f$ Q_k \f$ , the covrariance of the process noise; \f$ R_k \f$ , covariance\n
 * of the observation noise; and sometimes \f$ B_k \f$ , the control-input model, for each time-step, \f$ k \f$ , as\n
 * describe as below:\n
 * \f[ X_k = F_kX_{k-1} + B_ku_k + w_k \f]
 */
int kalman();
/**
 * Initialize the Kalman filter
 *
 * @param kalman The pointer to the kalman structure
 * @return None
 */
void kalman_init(struct kalman_t *kalman);

/**
 * Kalman Time Update("Predict") \n
 * (1)Project the state ahead
 * \f[ \hat{x}^{-}_{k} = A \hat{x}_{k - 1} + B u_{k - 1} \f]
 * (2)Project the error covariance ahead
 * \f[ P^{-}_{k} = A P_{k - 1} A^{T} + Q \f] 
 *
 * @param kalman The pointer to the kalman structure
 * @param None
 * @sa kalman_correct
 */
void kalman_predict(struct kalman_t *kalman);

/**
 * Kalman Measurement Update("Correct")
 *
 * (1)Compute the Kalman gian
 * \f[ K_{k} = P^{-}_{k} H^{T} \left( H P^{-}_{k} H^{T} + R \right)^{-1} \f]
 * (2)Update estimate with measurement \f$ z_k \f$
 * \f[ \hat{x}_{k} = \hat{x}^{-}_{k} + K_{k} \left( z_{k} - H \hat{x}^{-}_{k} \right) \f]
 * (3)Update the error covariance
 * \f[ P_{k} = \left( I - K_{k} H \right) P^{-}_{k} \f]
 *
 * @param kalman The pointer to the kalman structure
 * @return None
 * @sa kalman_predict
 */
void kalman_correct(struct kalman_t *kalman);


/**
 * Extend Kalman Filtering
 */
typedef struct ext_kalman_t {
} ext_kalman_t;


/** @} */

/** @} */

#endif /* _KALMAN_H */
