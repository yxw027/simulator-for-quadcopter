#include <stdio.h>
#include "stm32f10x.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "bsp.h"

/*
 * Configure the clocks, GPIO and other peripherals as required by the demo.
 */
//static void prvSetupHardware( void );
extern void initTask_init(void);
extern void vAttitudeTask_init(void);
int main()
{
    bsp_init();
    printf("hello world!\n");

    initTask_init();
    vAttitudeTask_init();
    vTaskStartScheduler();
}
