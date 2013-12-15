#include "freeRTOS.h"
#include "task.h"
#include "queue.h"

#include "led.h"

static xQueueHandle xLedQueue;

xQueueHandle xGetLedQueue(void)
{
    if (xLedQueue)
        return xLedQueue;
    else
        return 0;
}

void vTaskLed(void *args)
{
    portTickType xDelay = 1000 / portTICK_RATE_MS;
    portTickType xTime = xTaskGetTickCount();
    portTickType xTimeExpired;
    portTickType period;
    xLedQueue = xQueueCreate(1, sizeof(portTickType));
    if (xLedQueue == 0)
    {
        return;
    }
    for (;;)
    {
        led_toggle(LED_BLUE);
        if (xQueueReceive(xLedQueue, &period, (portTickType)0))
        {
            xDelay = period;
        }
        /*
        xTimeExpired = xTaskGetTickCount() - xTime;
        xTime = xTaskGetTickCount();
        if (xTimeExpired == xDelay)
        {
        }*/
        vTaskDelay(xDelay);
        
    }
}

void initTask_init(void)
{
    xTaskHandle xHandle = NULL;
    xTaskCreate(vTaskLed, (const signed portCHAR *)"init", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &xHandle);
    configASSERT(xHandle);
}
