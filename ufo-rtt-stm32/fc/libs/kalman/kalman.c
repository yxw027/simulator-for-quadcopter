/**
 * @file kalman.c
 * @brief kalman math implementation
 */

#include "kalman.h"

#include <stdio.h>

#define MAKE_A  "make_A()"

void kalman_init(struct kalman_t *kalman)
{
/* TODO some operations do not need, maybe change 
    if(kalman->make_A)
        printf("Warning: %s is not implemented", MAKE_A);
*/        
    assert(kalman->make_A != NULL);
    assert(kalman->make_H != NULL);
    assert(kalman->make_V != NULL);
    assert(kalman->make_R != NULL);
    assert(kalman->make_W != NULL);
    assert(kalman->make_Q != NULL);

    assert(kalman->make_process != NULL);
    assert(kalman->make_measure != NULL);
}

void kalman_predict(struct kalman_t *kalman)
{
    /* Project the state ahead */
    X_prior = A * X_post + B * U;
    /* Project the error covariance ahead */
    P_prior = A * P_post * A.transpose() + Q;
}

void kalman_correct(struct kalman_t *kalman)
{
    /* Innovation or measurement residual */
    /* Innovation (or residual) covariance */
    /* Compute the Kalman gian */
    K = P_prior * H.transpose() * (H * P_prior * H.transpose() + R).inverse();
    /* Update estimate with measurement \f$ z_k \f$ */
    X_post = X_prior + K * (z - H * X_prior);
    /* Update the error covariance */
    P_post = (I - K * H) * P_prior;
}