/*
 * @file FreeRTOS_stm32f10x_DriverInterface.c
 * @brief Switches control for the FreeRTOS+IO generic API to the FreeRTOS + IO
 * device specific API.
 */
#include <FreeRTOS_IO.h>
#include <queue.h>

portBASE_TYPE vFreeRTOS_stm32f10x_PopulateFunctionPointers( const Peripheral_Types_t ePeripheralType, Peripheral_Control_t * const pxPeripheralControl )
{
    portBASE_TYPE xReturn = pdFALSE;

    switch (ePeripheralType) {
    case eUART_TYPE:
    #if ioconfigINCLUDE_UART == 1
    {
        xReturn = FreeRTOS_UART_open( pxPeripheralControl );
    }
    #endif /* ioconfigINCLUDE_UART */
    break;

    case eSPI_TYPE:
        break;

    default:
        break;
    }

    return xReturn;
}
