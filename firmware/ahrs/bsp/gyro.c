gyro_calibration(struct gyro_bias_t *bias)
{
    int buf_size = sizeof(gyro_buf) / 4;
    
    bias->gyro_bias_x = gyro_buf_x / buf_size;
    bias->gyro_bias_y = gyro_buf_y / buf_size;
    bias->gyro_bias_z = gyro_buf_z / buf_size;
}