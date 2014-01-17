#include "FreeRTOS.h"

static portBASE_TYPE prvTaskStatusCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString)
{
    const int8_t *const pcTaskTableHeader = (int8_t *)"Task          State  Priority  Stack  #\r\n************************************************\r\n";

    strcpy((char *)pcWriteBuffer, (char *)pcTaskTableHeader);
    vTaskList(pcWriteBuffer + strlen(pcTaskTableHeader));

    return pdFALSE;
}

/**
 * @brief perform sensors calibration
 * usage: calibrate [accelerometer | gyroscope] [offset/bias]
 */
static portBASE_TYPE prvCalbibrationCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString)
{
    int8_t xSensorType = -1;
    int8_t *pcParameterString;
    portBASE_TYPE xParameterStringLength;
    pcParameterString = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParameterStringLength);

    if (strcmp(pcParameterString, "accelerometer"))
        xSensorType = 1;
    else if(strcmp(pcParameterString), "gyroscope")
        xSensorType = 2;

    pcParameterString = FreeRTOS_CLIGetParameter(pcCommandString, 2, &xParameterStringLength);
    if (strcmp(pcParameterString, "offset"))
        xSensorType = 1;
    else if(strcmp(pcParameterString), "gyroscope")
        xSensorType = 2;

    switch (xSensorType) {
    case 1:
        break;
    case 2:
        break;
    default:
        break;
    }
}

