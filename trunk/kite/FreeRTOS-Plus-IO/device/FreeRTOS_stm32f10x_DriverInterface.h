#ifndef FREERTOS_STM32F10X_DRIVER_INTERFACE_H
#define FREERTOS_STM32F10X_DRIVER_INTERFACE_H

#define boardAVAILABLE_DEVICES_LIST												\
{																				\
	{ ( const int8_t * const ) "/UART3/", eUART_TYPE, ( void * ) LPC_UART3 },	\
	{ ( const int8_t * const ) "/SSP1/", eSSP_TYPE, ( void * ) LPC_SSP1 },		\
	{ ( const int8_t * const ) "/I2C2/", eI2C_TYPE, ( void * ) LPC_I2C2 }		\
}

/*******************************************************************************
 * Map the FreeRTOS+IO interface to the STM32F10X specific functions.
 ******************************************************************************/
portBASE_TYPE vFreeRTOS_stm32f10x_PopulateFunctionPointers( const Peripheral_Types_t ePeripheralType, Peripheral_Control_t * const pxPeripheralControl );
#define boardFreeRTOS_PopulateFunctionPointers vFreeRTOS_stm32f10x_PopulateFunctionPointers

#endif /* FREERTOS_STM32F10X_DRIVER_INTERFACE_H */