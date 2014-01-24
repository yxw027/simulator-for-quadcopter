/**
 * @file cli.c
 * @brief Command Line Interface
 */
#include "FreeRTOS.h"
#include "task.h"

// #include "FreeRTOS_IO.h"

#include "FreeRTOS_CLI.h"

#define cmdMAX_INPUT_SIZE           64

#define cmd50ms     ((void *)(50UL / portTICK_RATE_MS))

static const int8_t * const pcWelcomeMessage = (int8_t *)"FreeRTOS command server.\r\nType Help to view a list of registered commands.\r\n\r\n>";
static const int8_t * const pcNewLine = (int8_t *)"\r\n";
static const int8_t * const pcEndOfCommandOutputString = (int8_t *)"\r\n[Press ENTER to execute the previous command again]\r\n>";

static Peripheral_Descriptor_t xConsoleUART = NULL;

static void vCommandConsleTask(void *pvParameters)
{
    int8_t cRxedChar, cInputIndex = 0, *pcOutputString;
    static int8_t cInputString[cmdMAX_INPUT_SIZE], cLastInputString[cmdMAX_INPUT_SIZE];
    portBASE_TYPE xReturned;

    xConsoleUART = FreeRTOS_open("/UART1/", ( uint32_t ) NULL);
    configASSERT(xConsoleUART);

    xReturned = FreeRTOS_ioctl(xConsoleUART, ioctlUSE_ZERO_COPY_TX, NULL);
    configASSERT(xReturned);

    xReturned = FreeRTOS_ioctl(xConsoleUART, ioctlUSE_CHARACTER_QUEUE_RX, (void *) cmdMAX_INPUT_SIZE);
    configASSERT(xReturned);

    if (FreeRTOS_ioctl(xConsoleUART, ioctlOBTAIN_WRITE_MUTEX, cmd50ms) == pdPASS)
    {
        FreeRTOS_write(xConsoleUART, pcWelcomeMessage, strlen(( char *)pcWelcomeMessage));
    }

    for (; ;) {
        /* Only interested in reading one character at a time. */
        FreeRTOS_read(xConsoleUART, &cRxedChar, sizeof(cRxedChar));

        /* Echo the character back. */
        if (FreeRTOS_ioctl(xConsoleUART, ioctlOBTAIN_WRITE_MUTEX, cmd50ms) == pdPASS) {
            FreeRTOS_write(xConsoleUART, &cRxedChar, sizeof(cRxedChar));
        }

        if (cRxedChar == '\n') {
            if (FreeRTOS_ioctl(xConsoleUART, ioctlOBTAIN_WRITE_MUTEX, cmd50ms) == pdPASS) {
                FreeRTOS_write(xConsoleUART, pcNewLine, strlen((char *)pcNewLine));
            }

            if (cInputIndex == 0)
                strcpy((char *)cInputString, (char *)cLastInputString);

            do {
                xReturned = FreeRTOS_ioctl(xConsoleUART, ioctlOBTAIN_WRITE_MUTEX, cmd50ms);
                if (xReturned == pdPASS) {
                    xReturned = FreeRTOS_CLIProcessCommand(cInputString, pcOutputString, configCOMMAND_INT_MAX_OUTPUT_SIZE);

                    FreeRTOS_write(xConsoleUART, pcOutputString, strlen((char *)pcOutputString));
                }
            } while (xReturned != pdFALSE);

            strcpy((char *)cLastInputString, cInputString);
            cInputIndex = 0;
            memset(cInputString, 0x00, cmdMAX_INPUT_SIZE);

            /* Ensure the last string to be transmitted has completed. */
            if (FreeRTOS_ioctl(xConsoleUART, ioctlOBTAIN_WRITE_MUTEX, cmd50ms) == pdPASS)
            {
                /* Start to transmit a line separator, just to make the output
                easier to read. */
                FreeRTOS_write(xConsoleUART, pcEndOfCommandOutputString, strlen((char *)pcEndOfCommandOutputString));
            }
        } else {
            if (cRxedChar == '\r') {

            } else if (cRxedChar == '\b') {
                if (cInputIndex > 0) {
                    cInputString[cInputIndex--] = '\0';
                }
            } else {
                if ((cRxedChar >= ' ') && (cRxedChar <= '~')) {
                    if (cInputIndex < cmdMAX_INPUT_SIZE) {
                        cInputString[cInputIndex++] = cRxedChar;
                    }
                }
            }
        }
    }
}

void vCommandConsoleTaskInit(void)
{
    xTaskHandle xHandle = NULL;
    xTaskCreate(vCommandConsleTask, (const signed portCHAR *)"CLI", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &xHandle);
    configASSERT(xHandle);
}
