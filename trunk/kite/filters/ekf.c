#include <stdio.h>
#include <stdlib.h>

#include "ekf.h"

/**
 * @addtogroup kalman Extended Kalman Filter
 * @{
 */

struct ekf *ekf_new(int n, int m, int nw, int nv)
{
    struct ekf *ekf = malloc(sizeof(struct ekf));
    if (ekf) {
        /* X(nx1) */
        ekf->X = matrix_new(n, 1);
        /* P(nxn) */
        ekf->P = matrix_new(n, n);
        /* A(nxn) */
        ekf->A = matrix_new(n, n);
        /* H(mxn) */
        ekf->H = matrix_new(n, m);
        /* V(nxnw) */
        ekf->V = matrix_new(m, nv);
        /* R(mxm) */
        ekf->R = matrix_new(m, m);
        /* W(nxnw) */
        ekf->W = matrix_new(n, nw);
        /* Q(nxn) */
        ekf->Q = matrix_new(n, n);
        /* E(?x?) */
        /* K(nxm) */
        ekf->K = matrix_new(n, m);

        /* Tnxm(nxm) */
        ekf->Tnxm = matrix_new(n, m);
        /* Tnxn(nxn) */
        ekf->Tnxn = matrix_new(n, n);
        /* Tmxm(mxm) */
        ekf->Tmxm = matrix_new(m, m);

        ekf->n = n;
        ekf->m = m;
        ekf->nw = nw;
        ekf->nv = nv;
    }

    return ekf;
}

void ekf_delete(struct ekf *ekf)
{
    if (ekf) {
        if (ekf->X)
            matrix_delete(ekf->X);
        if (ekf->P)
            matrix_delete(ekf->P);
        if (ekf->Q)
            matrix_delete(ekf->Q);
        if (ekf->R)
            matrix_delete(ekf->R);
        if (ekf->A)
            matrix_delete(ekf->A);
        if (ekf->H)
            matrix_delete(ekf->H);
        if (ekf->K)
            matrix_delete(ekf->K);

        free(ekf);
    }
}

void ekf_init(struct ekf *ekf, matrix_t *Q, matrix_t *R)
{
    if (Q != NULL)
        ekf->Q = Q;
    if (R != NULL)
        ekf->R = R;
}

void ekf_predict(struct ekf *ekf, double u[], double dt)
{
    ekf->make_A(ekf);
    if (ekf->make_W)
        ekf->make_W(ekf);
    ekf->make_process(ekf);
    ekf->make_P(ekf);
}

void ekf_correct(struct ekf *ekf, double z[])
{
    ekf->make_H(ekf);
    if (ekf->make_V)
        ekf->make_V(ekf);
    ekf->make_measure(ekf);
}

void *ekf_get_data(struct ekf *ekf)
{
    return ekf->data;
}

void ekf_set_data(struct ekf *ekf, void *data)
{
    ekf->data = data;
}

/**
 * @}
 */
