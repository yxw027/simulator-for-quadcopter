#include "FreeRTOS.h"
#include "task.h"

#include "FreeRTOS_CLI.h"

static portBASE_TYPE prvTaskStatsCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString)
{
    const int8_t *const pcTaskTableHeader = (int8_t *)"Task          State  Priority  Stack  #\r\n************************************************\r\n";

    strcpy((char *)pcWriteBuffer, (char *)pcTaskTableHeader);
    vTaskList(pcWriteBuffer + strlen(pcTaskTableHeader));

    return pdFALSE;
}

static const CLI_Command_Definition_t prvTaskStatsCommandDefinition = {
    (const int8_t * const)"task-stats", /* The command string to type. */
    (const int8_t * const)"task-stats:\r\n Displays a table showing the state of each FreeRTOS task\r\n\r\n",
    prvTaskStatsCommand, /* The function to run. */
    0 /* No parameters are expected. */
};

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

static const CLI_Command_Definition_t prvCalibrationCommandDefinition = {
    (const int8_t * const)"cali", /* The command string to type. */
    (const int8_t * const)"task-stats:\r\n Displays a table showing the state of each FreeRTOS task\r\n\r\n",
    prvTaskStatsCommand, /* The function to run. */
    0 /* No parameters are expected. */
};

void vRegisterCLICommands(void)
{
    /* Register all the command line commands defined immediately above. */
    FreeRTOS_CLIRegisterCommand(&prvTaskStatsCommandDefinition);
    FreeRTOS_CLIRegisterCommand(&prvCalibrationCommandDefinition);
    // FreeRTOS_CLIRegisterCommand( &prvThreeParameterEchoCommandDefinition );
    // FreeRTOS_CLIRegisterCommand( &prvMultiParameterEchoCommandDefinition );
    // FreeRTOS_CLIRegisterCommand( &prvCreateTaskCommandDefinition );
    // FreeRTOS_CLIRegisterCommand( &prvDeleteTaskCommandDefinition );
}
