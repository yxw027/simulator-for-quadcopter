#ifndef FREERTOS_STM32F10X_DRIVER_INTERFACE_H
#define FREERTOS_STM32F10X_DRIVER_INTERFACE_H

#include <FreeRTOS.h>

#include <stm32f10x.h>

#define boardAVAILABLE_DEVICES_LIST                                             \
{                                                                               \
    { ( const int8_t * const ) "/UART1/", eUART_TYPE, ( void * ) USART1 },      \
    { ( const int8_t * const ) "/SPI1/", eSPI_TYPE, ( void * ) SPI1 },          \
    { ( const int8_t * const ) "/I2C2/", eI2C_TYPE, ( void * ) I2C1 }           \
}

/*******************************************************************************
 * Map the FreeRTOS+IO interface to the STM32F10X specific functions.
 ******************************************************************************/
portBASE_TYPE vFreeRTOS_stm32f10x_PopulateFunctionPointers( const Peripheral_Types_t ePeripheralType, Peripheral_Control_t * const pxPeripheralControl );
#define boardFreeRTOS_PopulateFunctionPointers vFreeRTOS_stm32f10x_PopulateFunctionPointers

portBASE_TYPE FreeRTOS_UART_open( Peripheral_Control_t * const pxPeripheralControl );
portBASE_TYPE FreeRTOS_UART_ioctl( Peripheral_Descriptor_t pxPeripheral, uint32_t ulRequest, void *pvValue );
size_t FreeRTOS_UART_read( Peripheral_Descriptor_t const pxPeripheral, void * const pvBuffer, const size_t xBytes );
size_t FreeRTOS_UART_write( Peripheral_Descriptor_t const pxPeripheral, const void *pvBuffer, const size_t xBytes );

#endif /* FREERTOS_STM32F10X_DRIVER_INTERFACE_H */
