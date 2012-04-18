/**
 * @file main.c
 * @brief The program entry
 */



extern double q0, q1, q2, q3;
extern double psi, theta, psi;
extern double ax, ay, az;
extern double p, q, r;
extern double bp, bq, br;
extern double m[];
double time;
double dt;

int main()
{
    int i;
    uart_init();
    
    /* Wait until adc samples are ready. */
    while (!accel_is_ready());
    for (i = 0; i < 16; i++)
        accel_get_value(&ax, &ay, &az);
    roll/theta = atan2(ay, az);
    pitch = atan2(ax, az);
    Xh = mx * cos(pitch) + my * sin(roll) * sin(pitch) + mz
    Yh = mx * cos(roll) + my * sin(roll);
    yaw = atan2(Yh, Xh);
    for (; ;) {
        if (accel_is_ready()) {
            double cur_time;

            accel_get_value(a);
            cur_time = get_time();
            dt = cur_time - time;
            time = cur_time;
            

            ext_kalman_predict();
            ext_kalman_correct();
            spi_write(buf, len);
    }
}
