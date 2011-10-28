Accel_calibration(struct accel_offset *offset)
{

}


    
IMU_Init()
{
    /* hardware initialization */
    Accel_init();
    Gyro_init();
    
    Accel_calibration();
    Gyro_calibration();
}


int check();