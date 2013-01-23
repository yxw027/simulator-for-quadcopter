#include <string.h>

#include "ekf.h"

#define N   7
#define M   3
#define NV
#define NW

struct kalman_data {
    double u[3];
    double dt;
    double unused[3]; /* place holder */
    double z[3];
};

static void make_A(struct ekf *ekf)
{
//    struct kalman_data *data = (struct kalman_data *)ekf->data;
    matrix_t *X = ekf->X;
    double q0 = M_INDEX(X, 0, 0);
    double q0 = M_INDEX(X, 1, 0);
    double q0 = M_INDEX(X, 2, 0);
    double q0 = M_INDEX(X, 3, 0);    
    double p = u[0] - M_INDEX(X, 4, 0);
    double q = u[1] - M_INDEX(X, 5, 0);
    double r = u[2] - M_INDEX(X, 6, 0);
    
    double array[7][7] = {
        { 0, -p, -q, -r,  q1,  q2,  q3 },
        { p,  0,  r, -q,   0,   0,   0 },
        { q, -r,  0,  p, -q3, -q0,  q1 },
        { r,  q, -p,  0,  q2, -q1, -q0 },
        { 0,  0,  0,  0,   0,   0,   0 },
        { 0,  0,  0,  0,   0,   0,   0 },
        { 0,  0,  0,  0,   0,   0,   0 },
    };
    memset(X->data, 0, X->rows * X->cols * sizeof(double));   //??????????????????
    memcpy(X->data, array, X->rows * X->cols * sizeof(double)); //?????????????
}

static void make_H(struct ekf *ekf)
{
//    struct kalman_data *data = (struct kalman_data *)ekf->data;
    matrix_t *h = ekf->H;
    memset(h->data, 0, h->rows * h->cols * sizeof(double));

//    M_INDEX(h, 0, 0) = 0;
}

static void make_V(struct ekf *ekf)
{
}

static void make_R(struct ekf *ekf)
{
}

static void make_W(struct ekf *ekf)
{
    /* FIXME: No idea about this */
    matrix_t *w = ekf->W;
    double q0 = M_INDEX(x, 0, 0);
    double q1 = M_INDEX(x, 1, 0);
    double q2 = M_INDEX(x, 2, 0);
    double q3 = M_INDEX(x, 3, 0);

    M_INDEX(w, 6, 0) = q1 / 2;
    M_INDEX(w, 6, 1) = q2 / 2;
    M_INDEX(w, 6, 2) = q3 / 2;
    M_INDEX(w, 7, 0) = -q0 / 2;
    M_INDEX(w, 7, 1) = q3 / 2;
    M_INDEX(w, 7, 2) = -q2 / 2;
    M_INDEX(w, 8, 0) = -q3 / 2;
    M_INDEX(w, 8, 1) = -q0 / 2;
    M_INDEX(w, 8, 2) = q1 / 2;
    M_INDEX(w, 9, 0) = q2 / 2;
    M_INDEX(w, 9, 1) = -q1 / 2;
    M_INDEX(w, 9, 2) = -q0 / 2;

    M_INDEX(w, 10, 6) = 1;
    M_INDEX(w, 11, 7) = 1;
    M_INDEX(w, 12, 8) = 1;
}

static void make_Q(struct ekf *ekf)
{
}

static void make_P(struct ekf *ekf)
{
#if 0
    /*
     * continuous update
     * Pdot = A * P + P * A' + Q
     */
#ifdef EKF_UPDATE_CONTINUOUS
    matrix_mult(ekf->Tnxn, ekf->A, ekf->P);
    matrix_transpose(ekf->T1nxn, ekf->A);
    matrix_mult(ekf->tnxn, ekf->P, ekf->T1nxn);
    matrix_add(ekf->Pdot, ekf->Tnxn);
    matrix_add(ekf->Pdot, ekf->tnxn);
    matrix_add(ekf->Pdot, ekf->Q);
#endif
    /*
     * discrete update
     * Pdot = A * P * A' + Q
     */
#ifdef EKF_UPDATE_DISCRETE
    matrix_transpose(ekf->Tnxn, ekf->A);
    matrix_mult(ekf->T1nxn, ekf->A, ekf->P);
    matrix_mult(ekf->tnxn, ekf->Tnxn, ekf->Tnxn);
    matrix_add(ekf->Pdot, ekf->Tnxn, ekf->Q);
#endif
    /* P = P + Pdot * dt */
//    matrix_smult(ekf->Pdot, dt);
    matrix_add(ekf->P, ekf->P, ekf->Pdot);
#endif
}

static void make_process(struct ekf *ekf)
{
    struct kalman_data *data = (struct kalman_data *)ekf->data;
    matrix_t *x = ekf->X;
    matrix_t *Xdot = matrix_new(N, 1);
    if (!Xdot)
        return;
    // TODO: type double is not suitable
    double p = data->u[0] - M_INDEX(x, 4, 0);
    double q = data->u[1] - M_INDEX(x, 5, 0);
    double r = data->u[2] - M_INDEX(x, 6, 0);

    double q0 = M_INDEX(x, 0, 0);
    double q1 = M_INDEX(x, 1, 0);
    double q2 = M_INDEX(x, 2, 0);
    double q3 = M_INDEX(x, 3, 0);

    M_INDEX(Xdot, 0, 0) = (-p * q1 - q * q2 - r * q3) * data->dt / 2;
    M_INDEX(Xdot, 1, 0) = (p * q0 - q * q3 + r * q2) * data->dt / 2;
    M_INDEX(Xdot, 2, 0) = (p * q3 + q * q0 - r * q1) * data->dt / 2;
    M_INDEX(Xdot, 3, 0) = (-p * q2 + q * q1 + r * q0) * data->dt / 2;
    M_INDEX(Xdot, 4, 0) = 0;
    M_INDEX(Xdot, 5, 0) = 0;
    M_INDEX(Xdot, 6, 0) = 0;

    matrix_add(ekf->X, ekf->X, Xdot);

    matrix_delete(Xdot);
}

static void make_measure(struct ekf *ekf)
{
}

static void callback(struct ekf *ekf)
{
}

void ahrs_init(struct ekf *ekf, struct kalman_data *data)
{
    ekf_init(ekf, NULL, NULL);

    ekf->make_A = make_A;
    ekf->make_H = make_H;
    ekf->make_V = make_V;
    ekf->make_R = make_R;
    ekf->make_W = make_W;
    ekf->make_Q = make_Q;
    ekf->make_P = make_P;
    ekf->make_process = make_process;
    ekf->make_measure = make_measure;
    ekf->callback = callback;
    ekf->data = data;
}

int main(int argc, char *argv[])
{
    struct ekf *ekf = ekf_new(7, 3, 0, 0);
    struct kalman_data kdata;

    ahrs_init(ekf, &kdata);
    ekf_predict(ekf, kdata.u, kdata.dt);
    ekf_correct(ekf, kdata.unused);
    return 0;
}
