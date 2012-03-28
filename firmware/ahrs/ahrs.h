/**
 * @file ahrs.h
 * @brief Attitude and Heading Renference System interface 
 */



/*
double x[N];
//    double u[3];
double z[M];
double A[N][N];
double P[2][2];  
double W[N][NV];
double Q[1][1];
double H[M][N];
double V[M][NV];
double R[1][1]; // TODO
void *data;
*/

extern void ahrs_init();
extern void ahrs_time_update_step();
extern void ahrs_measure_update_step();
extern void ahrs_get_x();
