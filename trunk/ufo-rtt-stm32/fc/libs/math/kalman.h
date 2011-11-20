/**
 * @file kalman.h
 * @brief Kalman filter interface
 *
 * This file contains the code for a kalman filter, an
 * extended kalman filter, and an iterated extended kalman filter.
 */

#ifndef _KALMAN_H
#define _KALMAN_H

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup math
 * @{
 */

/**
 * @defgroup kalman
 * kalman support
 * @{
 */

/**
 * @struct kalman_t kalman.h
 * @brief Describe a Kalman filter
 */ 
typedef struct kalman_t {
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
 * \f[ X_k = F_kX_k-1 + B_ku_k + w_k \f]
 */
int kalman();
/**
 * Extend Kalman Filtering
 */

/** @} */

/** @} */

/** @} */

#endif /* _KALMAN_H */
