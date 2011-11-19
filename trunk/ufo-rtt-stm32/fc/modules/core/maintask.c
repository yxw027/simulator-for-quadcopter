#include "debug.h"

#include "hardware/IGyro.h"
#include "hardware/IAccelerometor.h"


#include "task.h"


Accel_calibration(struct accel_offset *offset)
{

}


   
init_IMU()
{
    /* hardware initialization */
    init_hw_accl();
    init_hw_gyro();
    
    Accel_calibration();
    Gyro_calibration();
}


/**
 * flight control core
 */
void main_task(void *arg)
{
    struct main_tast_data *data = arg;
    
    /* init hardware */
    init_IMU();
    
    /* init private data */
    /*data->quaternion;
    data->euler.pitch;*/
    
    //self_check();
    /* main loop */
    while (1) {
    }
    
    /* never return */
}

static int self_check(void *data)
{
}

static int take_off();
