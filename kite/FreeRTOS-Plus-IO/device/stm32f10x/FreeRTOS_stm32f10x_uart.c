/**
 * @file FreeRTOS_stm32f10x_uart.c
 * @brief Implementation of the FreeRTOS+IO UART driver.
 */
#include <FreeRTOS.h>
#include <FreeRTOS_IO.h>

static size_t FreeRTOS_UART_read( Peripheral_Descriptor_t const pxPeripheral, void * const pvBuffer, const size_t xBytes )
{

}

static size_t FreeRTOS_UART_write( Peripheral_Descriptor_t const pxPeripheral, const void *pvBuffer, const size_t xBytes )
{

}

static portBASE_TYPE FreeRTOS_UART_ioctl( Peripheral_Descriptor_t pxPeripheral, uint32_t ulRequest, void *pvValue )
{
	portBASE_TYPE xReturn = pdPASS;

	switch (ulRequest) {
	case ioctlUSE_INTERRUPTS:
		break;
	default:
		break;
	}

	return xReturn;
}

portBASE_TYPE FreeRTOS_UART_open( Peripheral_Control_t * const pxPeripheralControl )
{
	portBASE_TYPE xReturn;
	const uint8_t cPeripheralNumber = pxPeripheralControl->cPeripheralNumber;

	if (cPeripheralNumber < 3/*MAX_UART_NUM*/) {
		pxPeripheralControl->read = FreeRTOS_UART_read;
		pxPeripheralControl->write = FreeRTOS_UART_write;
		pxPeripheralControl->ioctl = FreeRTOS_UART_ioctl;

		/* setup UART port */
		{

		}

		xReturn = pdPASS;
	} else {
		xReturn = pdFAIL;
	}

	return xReturn;
}
