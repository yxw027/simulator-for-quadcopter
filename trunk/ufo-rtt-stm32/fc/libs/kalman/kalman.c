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
    AX = matrix_mul(A, X);
    BU = matrix_mul(B, U);
    
    X = matrix_add(AX + BU);
    /* Project the error covariance ahead */
    AP = matrix_mul(A, P);
    APA = matrix_mul(AP, A.transpose());
    P = matrix_add(APA, Q);
}

void kalman_correct(struct kalman_t *kalman)
{
    /* Innovation or measurement residual */
    /* Innovation (or residual) covariance */
    /* Compute the Kalman gian */
    K = P * H.transpose() * (H * P * H.transpose() + R).inverse();
    /* Update estimate with measurement \f$ z_k \f$ */
    X = X + K * (z - H * X);
    /* Update the error covariance */
    P = (I - K * H) * P;
}