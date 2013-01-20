#include <string.h>

#include "ekf.h"

#define N 7
#define M 
struct kalman_data {
	double u[3];
	double dt;
	double unused[3]; /* place holder */
};

static void make_A(struct ekf *ekf)
{
//    struct kalman_data *data = (struct kalman_data *)ekf->data;
    matrix_t *x = ekf->X;
    double array[7][7] = {
	{1, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 1},
    };

    memcpy(x->data, array, x->rows * x->cols * sizeof(double));
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
    if (Xdot) {
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
    }
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
