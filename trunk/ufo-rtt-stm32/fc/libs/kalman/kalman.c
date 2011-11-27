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
    {
        AX = matrix_mul(A, X);
        BU = matrix_mul(B, U);
        
        matrix_add(AX, BU, X);
    }
    /* Project the error covariance ahead */
    {
        matrix_t AP = matrix_new(A->rows, P->cols);
        matrix_t At = matrix_new(A->cols, A->rows);
        matrix_t APAt = matrix_new(AP->rows, At->cols);
        
        matrix_mul(A, P, AP);
        matrix_transpose(A, At);
        matrix_mul(AP, At, APAt);
        matrix_add(APAt, Q, P);
        
        matrix_delete(AP);
        matrix_delete(At);
        matrix_delete(APAt);
    }
}

void kalman_correct(struct kalman_t *kalman)
{
    matrix_t *K = matrix_new(3, 3);
    
    /* Innovation or measurement residual */
    /* Innovation (or residual) covariance */
    /* Compute the Kalman gian */
    /* K = P * H.transpose() * (H * P * H.transpose() + R).inverse(); */
    {
        matrix_t *Ht = matrix_new(H->cols, H->rows);
        matrix_t *PHt = matrix_new(P->rows, Ht->cols);
        matrix_t *HP = matrix-new(H->rows, P->cols);
        matrix_t *HPHt = matrix_new(HP->rows, H_t->cols);
        matrix_t *HPHtR = matrix_new(R->rows, R->cols);
        matrix_t *HPHtR_I = matrix_new(HPHtR->rows, HPHtR->cols);
        
        matrix_transpose(H, Ht);
        matrix_mult(P, Ht, PHt);
        matrix_mult(H, P, HP);
        
        matrix_mult(HP, Ht, HPHt);
        matrix_add(HPHt, R, HPHtR);
        matrix_inverse(HPHtR, HPHtR_I);
        
        matrix_mult(PHt, HPHtR_I, K);
        
        matrix_delete(Ht);
        matrix_delete(PHt);
        matrix_delete(HP);
        matrix_delete(HPHt);
        matrix_delete(HPHtR);
    }    
    /* Update estimate with measurement \f$ z_k \f$ */
    /* X = X + K * (z - H * X); */
    
    /* Update the error covariance */
    /* P = (I - K * H) * P; */
    {
        matrix_t *KH = matirx_new(K->rows, H->cols);
        matrix_t *IKH = matrix_new(KH->rows, KH->cols);
        
        matrix_mult(K, H, KH);
        matrix_sub(I, KH, IKH);
        matrix_mult(IKH, P, P);
        
        matrix_delete(KH);
        matrix_delete(IKH);
    }
    matrix_delete(K);
}