
void ahrs_init()
{
    init_IMU();
    ext_kalman_initial();
}

void ahrs_update()
{

    /* high update rate, 50Hz */
    ext_kalman_predict();

    /* low update rate, 4Hz */
    ext_kalman_correct();
}