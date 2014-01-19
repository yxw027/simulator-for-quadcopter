#include <stdio.h>
#include "stm32f10x.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "bsp.h"

extern void vAttitudeTask_init(void);
extern void vCommandConsoleTaskInit(void);
int main()
{
    bsp_init();
	printf("hello world!\n");

    vAttitudeTask_init();

    vCommandConsoleTaskInit();

    vTaskStartScheduler();
}
