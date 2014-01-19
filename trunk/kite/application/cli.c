/**
 * @file cli.c
 * @brief Command Line Interface
 */
#include <FreeRTOS.h>
#include <task.h>

#include "FreeRTOS_IO.h"

#include <FreeRTOS_CLI.h>

#define cmdMAX_INPUT_SIZE           64

#define cmd50ms                     ( ( void * ) ( 50UL / portTICK_RATE_MS ) )

static const int8_t * const pcWelcomeMessage = ( int8_t * ) "FreeRTOS command server.\r\nType Help to view a list of registered commands.\r\n\r\n>";

static Peripheral_Descriptor_t xConsoleUART = NULL;

static portBASE_TYPE xHelloWorld(int8_t *pcWriteBuffer,
                                  size_t xWriteBufferLen,
                                  const int8_t *pcCommandString)
{

    return pdFALSE;
}

static const CLI_Command_Definition_t xHelloWorldCommand = {
        "helloworld",
        "helloworld help\n",
        xHelloWorld,
};

static void vCommandConsleTask(void *pvParameters)
{
    portBASE_TYPE xReturned;

    xConsoleUART = FreeRTOS_open( "/UART1/", ( uint32_t ) NULL );
    configASSERT( xConsoleUART );

    xReturned = FreeRTOS_ioctl( xConsoleUART, ioctlUSE_ZERO_COPY_TX, NULL );
    configASSERT( xReturned );

    xReturned = FreeRTOS_ioctl( xConsoleUART, ioctlUSE_CHARACTER_QUEUE_RX, ( void * ) cmdMAX_INPUT_SIZE );
    configASSERT( xReturned );

    if( FreeRTOS_ioctl( xConsoleUART, ioctlOBTAIN_WRITE_MUTEX, cmd50ms ) == pdPASS )
    {
        FreeRTOS_write( xConsoleUART, pcWelcomeMessage, strlen( ( char * ) pcWelcomeMessage ) );
    }
    // FreeRTOS_CLIRegisterCommand(&xHelloWorldCommand);

    for (; ;) {

    }
}

void vCommandConsoleTaskInit(void)
{
    xTaskHandle xHandle = NULL;
    xTaskCreate(vCommandConsleTask, (const signed portCHAR *)"CLI", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &xHandle);
    configASSERT(xHandle);
}
