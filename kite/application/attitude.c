#include "freeRTOS.h"
#include "task.h"
#include "queue.h"

extern xQueueHandle xGetLedQueue(void);

void vAttitudeTask(void *arg)
{
    portTickType period = 500 / portTICK_RATE_MS;

    for (;;)
    {
        vTaskDelay(period * 20 * 5);
        xQueueSend(xGetLedQueue(), &period, (portTickType)0);
        period -= 100;
    }
}

void vAttitudeTask_init(void)
{
    xTaskHandle xHandle = NULL;
    xTaskCreate(vAttitudeTask, (const signed portCHAR *)"attitude", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &xHandle);
    configASSERT(xHandle);
}