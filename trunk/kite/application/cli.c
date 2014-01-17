#include <string.h>

#include "FreeRTOS.h"

#include "FreeRTOS_IO.h"
#define cmd50ms     ((void *)(50UL / portTICK_RATE_MS))

#define cmdMAX_INPUT_SIZE   8

static const int8_t * const pcWelcomeMessage = (int8_t *)"FreeRTOS command server.\r\nType Help to view a list of registered commands.\r\n\r\n>";
static const int8_t * const pcNewLine = (int8_t *)"\r\n";

static Peripheral_Descriptor_t xConsoleUART = NULL;
static xTaskHandle xCLITaskHandle = NULL;

static void prvCLITask(void *pvParammeters)
{
    portBASE_TYPE portBASE_TYPE xReturned;
    int8_t cRxedChar, cInputIndex = 0, *pcOutputString;
    static int8_t cInputString[ cmdMAX_INPUT_SIZE ], cLastInputString[ cmdMAX_INPUT_SIZE ];

    xConsoleUART = FreeRTOS_open("UART1", NULL);
    configASSERT(xConsoleUART);

    xReturned = FreeRTOS_iotcl(xConsoleUART, ioctlUSE_ZERO_COPY_TX, NULL);
    configASSERT(xReturned);

    xReturned = FreeRTOS_iotcl(xConsoleUART, ioctlUSE_CHARACTER_QUEUE_RX, NULL);
    configASSERT(xReturned);

    if (FreeRTOS_ioctl(xConsoleUART, ioctlOBTAIN_WRITE_MUTEX, cmd50ms)) {
        FreeRTOS_write(xConsoleUART, pcWelcomeMessage, strlen((char *)pcWelcomeMessage));
    }

    for (; ;) {
        FreeRTOS_read(xConsoleUART, cRxedChar, sizeof(cRxedChar));

        if (FreeRTOS_ioctl(xConsoleUART, ioctlOBTAIN_WRITE_MUTEX, cmd50ms)) {
            FreeRTOS_write(xConsoleUART, cRxedChar, sizeof(cRxedChar));
        }

        if (cRxedChar == '\n') {
            if (FreeRTOS_ioctl(xConsoleUART, ioctlOBTAIN_WRITE_MUTEX, cmd50ms))
                FreeRTOS_write(xConsoleUART, pcNewLine, strlen((char *)pcNewLine));
            // TODO:

            strcpy((char *)cLastInputString, (char *)cInputString);
        } else {
            if (cRxedChar == '\r') {
                /* ignore the character */
            } else if (cRxedChar == '\b') {
                if (cInputIndex > 0) {
                    cInputString[--cInputIndex] = '\0';
                }
            } else {
                if (cRxedChar >= ' ' && cRxedChar <= '~') {
                    if (cInputIndex < cmdMAX_INPUT_SIZE) {
                        cInputString[cInputIndex++] = cRxedChar;
                    }
                }
            }
        }
    }
}
#define configCLI_TASK_STACK_SIZE   1
#define configCLI_TASK_PRIORITY     1
void CLITaskStart(void)
{
    xTaskCreate(prvCLITask,
            (const uint8_t *)"CLI",
            configCLI_TASK_STACK_SIZE,
            NULL,
            configCLI_TASK_PRIORITY,
            &xCLITaskHandle);
}
