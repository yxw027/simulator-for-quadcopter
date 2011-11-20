#include "debug.h"

#include "hal/IGyro.h"
#include "hal/IAccelerometor.h"


#include "task.h"

static struct core_task_data core_task_data;

/**
 * forward declare
 */
static void init_IMU();
static void self_check();
static int take_off();

void core_task_init()
{
    /* init hardware */
    init_IMU();
    /* self check */
    self_check();
    /* create core task */
    core_task(core_task_data);
}

/**
 * core task flight control 
 */
void core_task(void *arg)
{
    struct core_tast_data *data = arg;

    /* init private data */
    /*data->quaternion;
    data->euler.pitch;*/
    

    /* main loop */
    while (1) {
    }
    
    /* never return */
}


static void init_IMU()
{
    /* hardware initialization */
    init_hw_accl();
    init_hw_gyro();
    
    Accel_calibration();
    Gyro_calibration();
}


static void self_check()
{
}

static int take_off()
{
}
/*
Accel_calibration(struct accel_offset *offset)
{

}*/