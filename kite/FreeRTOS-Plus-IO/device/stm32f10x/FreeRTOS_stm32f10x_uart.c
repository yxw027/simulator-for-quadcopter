/**
 * @file FreeRTOS_stm32f10x_uart.c
 * @brief Implementation of the FreeRTOS+IO UART driver.
 */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
//#include <semphr.h>
#include <stdio.h>
#include <FreeRTOS_IO.h>

//#include <FreeRTOSIOConfig.h>
#include <FreeRTOS_DriverInterface.h>
#include <IOUtils_Common.h>
#include "stm32f10x.h"

static GPIO_InitTypeDef GPIO_InitStructure;
static USART_InitTypeDef USART_InitStructure;
static NVIC_InitTypeDef NVIC_InitStructure;

static size_t prvFillFifoFromBuffer( USART_TypeDef * const pxUART, uint8_t **ppucBuffer, const size_t xTotalBytes )
{
    size_t xBytesSent = 0U;

    /* This function is only used by zero copy transmissions, so mutual
    exclusion is already taken care of by the fact that a task must first
    obtain a semaphore before initiating a zero copy transfer.  The semaphore
    is part of the zero copy structure, not part of the application. */
    /*while( ( pxUART->FIFOLVL & uartTX_FIFO_LEVEL_MASK ) != uartTX_FIFO_LEVEL_MASK )
    {
        if( xBytesSent >= xTotalBytes )
        {
            break;
        }
        else
        {
            pxUART->THR = **ppucBuffer;
            ( *ppucBuffer )++;
            xBytesSent++;
        }
    }*/

    if( xBytesSent >= xTotalBytes )
    {
    }
    else
    {
        USART_SendData(USART1, (uint8_t) **ppucBuffer);
        ( *ppucBuffer )++;
        xBytesSent++;
    }

    return xBytesSent;
}
/*
 * Stores the transfer control structures that are currently in use by the
 * supported UART ports.
 */
static Transfer_Control_t *pxTxTransferControlStructs[ 3 ] = { NULL };
static Transfer_Control_t *pxRxTransferControlStructs[ 3 ] = { NULL };

/**
 * @brief  Configures the different system clocks.
 * @param  None
 * @retval None
 */
static void RCC_Configuration(void)
{
    /* Enable GPIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    /* Enable USART1 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}

/**
 * @brief  Configures the different GPIO ports.
 * @param  None
 * @retval None
 */
static void GPIO_Configuration(void)
{
    /* Configure USART1 TX as alternate function push-pull */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure USART1 RX as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief  Configures the nested vectored interrupt controller.
 * @param  None
 * @retval None
 */
static void NVIC_Configuration(void)
{
    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    /* Enable the USART1 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static size_t FreeRTOS_UART_read(Peripheral_Descriptor_t const pxPeripheral, void * const pvBuffer, const size_t xBytes)
{
    Peripheral_Control_t * const pxPeripheralControl = (Peripheral_Control_t * const)pxPeripheral;
    size_t xReturn = 0U;
    int8_t cPeripheralNumber;
    USART_TypeDef * const pxUART =
            (USART_TypeDef * const)diGET_PERIPHERAL_BASE_ADDRESS(((Peripheral_Control_t * const)pxPeripheral));

    if (diGET_RX_TRANSFER_STRUCT(pxPeripheralControl) == NULL) {
    #if ioconfigUSE_UART_POLLED_RX == 1
    {
        /* No FreeRTOS objects exist to allow reception without blocking
         the task, so just receive by polling.  No semaphore or queue is
         used here, so the application must ensure only one task attempts
         to make a polling read at a time. */
        xReturn = USART_ReceiveData(pxUART);
        //*pvBuffer[0] = xReturn;
        //xBytes = 1;
    }
    #endif /* ioconfigUSE_UART_POLLED_RX */
    } else {
        cPeripheralNumber = diGET_PERIPHERAL_NUMBER(pxPeripheralControl);

        switch (diGET_RX_TRANSFER_TYPE(pxPeripheralControl)) {
        case ioctlUSE_CIRCULAR_BUFFER_RX:
        #if ioconfigUSE_UART_CIRCULAR_BUFFER_RX == 1
        {
            /* There is nothing to prevent multiple tasks attempting to
             read the circular buffer at any one time.  The implementation
             of the circular buffer uses a semaphore to indicate when new
             data is available, and the semaphore will ensure that only the
             highest priority task that is attempting a read will actually
             receive bytes. */
            ioutilsRECEIVE_CHARS_FROM_CIRCULAR_BUFFER
            (
                    pxPeripheralControl,
                    USART_ITConfig(pxUART, USART_IT_RXNE, DISABLE), /* Disable peripheral. */
                    USART_ITConfig(pxUART, USART_IT_RXNE, ENABLE), /* Enable peripheral. */
                    ((uint8_t *)pvBuffer), /* Data destination. */
                    xBytes, /* Bytes to read. */
                    xReturn /* Number of bytes read. */
            );
        }
        #endif /* ioconfigUSE_UART_CIRCULAR_BUFFER_RX */
            break;

        case ioctlUSE_CHARACTER_QUEUE_RX:
        #if ioconfigUSE_UART_RX_CHAR_QUEUE == 1
        {
            /* The queue allows multiple tasks to attempt to read
             bytes, but ensures only the highest priority of these
             tasks will actually receive bytes.  If two tasks of equal
             priority attempt to read simultaneously, then the
             application must ensure mutual exclusion, as time slicing
             could result in the string being received being partially
             received by each task. */
            xReturn = xIOUtilsReceiveCharsFromRxQueue(pxPeripheralControl, (uint8_t *)pvBuffer, xBytes);
        }
        #endif /* ioconfigUSE_UART_RX_CHAR_QUEUE */
            break;

        default:
            /* Other methods can be implemented here. */
            configASSERT( xReturn );

            /* Prevent compiler warnings when the configuration is set such
             that the following parameters are not used. */
            (void) pvBuffer;
            (void) xBytes;
            (void) pxUART;
            break;
        }
    }

    return xReturn;
}

static size_t FreeRTOS_UART_write(Peripheral_Descriptor_t const pxPeripheral,
        const void *pvBuffer, const size_t xBytes)
{
    Peripheral_Control_t * const pxPeripheralControl = (Peripheral_Control_t * const)pxPeripheral;
    size_t xReturn = 0U;
    USART_TypeDef * const pxUART = (USART_TypeDef * const)diGET_PERIPHERAL_BASE_ADDRESS(((Peripheral_Control_t * const)pxPeripheral));
    int8_t cPeripheralNumber;

    if (diGET_TX_TRANSFER_STRUCT( pxPeripheralControl ) == NULL) {
    #if ioconfigUSE_UART_POLLED_TX == 1
    {
        /* No FreeRTOS objects exist to allow transmission without blocking
        the task, so just send out by polling.  No semaphore or queue is
        used here, so the application must ensure only one task attempts to
        make a polling write at a time. */
        // USART_Send(pxUART, *( uint8_t * ) pvBuffer[0] );

        /* The UART is set to polling mode, so may as well poll the busy bit
        too.  Change to interrupt driven mode to avoid wasting CPU time here. */
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);

        xReturn = 1;
    }
    #endif /* ioconfigUSE_UART_POLLED_TX */
    } else {
        /* Remember which transfer control structure is being used.
        The Tx interrupt will use this to continue to write data to the
        Tx FIFO/UART until the length member of the structure reaches
        zero. */
        cPeripheralNumber = diGET_PERIPHERAL_NUMBER(pxPeripheralControl);
        pxTxTransferControlStructs[cPeripheralNumber] = diGET_TX_TRANSFER_STRUCT(pxPeripheralControl);

        switch(diGET_TX_TRANSFER_TYPE(pxPeripheralControl))
        {
        case ioctlUSE_ZERO_COPY_TX:
        #if ioconfigUSE_UART_ZERO_COPY_TX == 1
        {
            /* The implementation of the zero copy write uses a semaphore
            to indicate whether a write is complete (and so the buffer
            being written free again) or not.  The semantics of using a
            zero copy write dictate that a zero copy write can only be
            attempted by a task, once the semaphore has been successfully
            obtained by that task.  This ensure that only one task can
            perform a zero copy write at any one time.  Ensure the semaphore
            is not currently available, if this function has been called
            without it being obtained first then it is an error. */
            configASSERT( xIOUtilsGetZeroCopyWriteMutex( pxPeripheralControl, ioctlOBTAIN_WRITE_MUTEX, 0U ) == 0 );
            xReturn = xBytes;
            ioutilsINITIATE_ZERO_COPY_TX(
                    pxPeripheralControl,
                    USART_ITConfig(pxUART, USART_IT_TXE, DISABLE),  /* Disable peripheral function. */
                    USART_ITConfig(pxUART, USART_IT_TXE, ENABLE),   /* Enable peripheral function. */
                    prvFillFifoFromBuffer(pxUART, (uint8_t **) & (pvBuffer), xBytes), /* Write to peripheral function. */
                    pvBuffer,                       /* Data source. */
                    xReturn                         /* Number of bytes to be written. This will get set to zero if the write mutex is not held. */
                );
        }
        #endif /* ioconfigUSE_UART_ZERO_COPY_TX */
            break;

        case ioctlUSE_CHARACTER_QUEUE_TX:
        #if ioconfigUSE_UART_TX_CHAR_QUEUE == 1
        {
            /* The queue allows multiple tasks to attempt to write
            bytes, but ensures only the highest priority of these tasks
            will actually succeed.  If two tasks of equal priority
            attempt to write simultaneously, then the application must
            ensure mutual exclusion, as time slicing could result in
            the strings being sent to the queue being interleaved. */
            ioutilsBLOCKING_SEND_CHARS_TO_TX_QUEUE(
                    pxPeripheralControl,
                    pdFALSE,  /* Peripheral busy condition. */
                    USART_SendData(pxUART, ucChar)      /* Peripheral write function. */
                    ((uint8_t *)pvBuffer),         /* Data source. */
                    xBytes,                             /* Number of bytes to be written. */
                    xReturn);
        }
        #endif /* ioconfigUSE_UART_TX_CHAR_QUEUE */
            USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
            break;

        default :
            /* Other methods can be implemented here.  For now set the
            stored transfer structure back to NULL as nothing is being
            sent. */
            configASSERT( xReturn );
            pxTxTransferControlStructs[ cPeripheralNumber ] = NULL;

            /* Prevent compiler warnings when the configuration is set such
            that the following parameters are not used. */
            ( void ) pvBuffer;
            ( void ) xBytes;
            ( void ) pxUART;
            break;
        }
    }

    return xReturn;
}

static portBASE_TYPE FreeRTOS_UART_ioctl(Peripheral_Descriptor_t pxPeripheral, uint32_t ulRequest, void *pvValue) {
    Peripheral_Control_t * const pxPeripheralControl = (Peripheral_Control_t * const) pxPeripheral;
    portBASE_TYPE xReturn = pdPASS;
    const int8_t cPeripheralNumber = diGET_PERIPHERAL_NUMBER(((Peripheral_Control_t * const)pxPeripheral));

    switch (ulRequest) {
    case ioctlSET_SPEED:
    {
        uint32_t ulValue = (uint32_t) pvValue;
        USART_InitStructure.USART_BaudRate = ulValue;
        /* USART1 configuration */
        USART_Init(USART1, &USART_InitStructure);
        break;
    }

    case ioctlSET_INTERRUPT_PRIORITY:
    {
        uint8_t ulValue = (uint8_t) pvValue;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = ulValue;
        NVIC_Init(&NVIC_InitStructure);
        break;
    }

    case ioctlUSE_INTERRUPTS:
    {
        uint32_t ulValue = (uint32_t) pvValue;
        if (ulValue == pdFALSE) {
            NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
            NVIC_Init(&NVIC_InitStructure);
        } else {
            USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
            // USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
            NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
            NVIC_Init(&NVIC_InitStructure);
        }
        break;
    }

    default:
        xReturn = pdFAIL;
        break;
    }

    return xReturn;
}

#define ioconfigINCLUDE_UART0 1
portBASE_TYPE FreeRTOS_UART_open(Peripheral_Control_t * const pxPeripheralControl)
{
    portBASE_TYPE xReturn;
    const uint8_t cPeripheralNumber = diGET_PERIPHERAL_NUMBER(pxPeripheralControl);

    if (cPeripheralNumber < 3/*MAX_UART_NUM*/) {
        pxPeripheralControl->read = FreeRTOS_UART_read;
        pxPeripheralControl->write = FreeRTOS_UART_write;
        pxPeripheralControl->ioctl = FreeRTOS_UART_ioctl;

        taskENTER_CRITICAL();
        {
            RCC_Configuration();
            GPIO_Configuration();
            NVIC_Configuration();
        }
        taskEXIT_CRITICAL();

        xReturn = pdPASS;
    } else {
        xReturn = pdFAIL;
    }
#if 0
    switch (cPeripheralNumber) {
    case 0:
    #if ioconfigINCLUDE_UART0 == 1
    {
    }
    #endif /* ioconfigINCLUDE_UART0 */
        break;

    case 1:
    #if ioconfigINCLUDE_UART1 == 1
    {
    }
    #endif /* ioconfigINCLUDE_UART1 */
        break;

    case 2:
    #if ioconfigINCLUDE_UART2 == 1
    {
    }
    #endif /* ioconfigINCLUDE_UART2 */
        break;

    default:
        break;
    }
#endif
    return xReturn;
}

void uart1_irq_handler(void)
{
    uint32_t ulReceived = 0;
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    const unsigned portBASE_TYPE uxUARTNumber = 1UL;
    Transfer_Control_t *pxTransferStruct;

    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        pxTransferStruct = pxRxTransferControlStructs[uxUARTNumber];
        if (pxTransferStruct != NULL) {
            switch(diGET_TRANSFER_TYPE_FROM_CONTROL_STRUCT(pxTransferStruct)) {
            case ioctlUSE_CIRCULAR_BUFFER_RX:
            #if ioconfigUSE_UART_CIRCULAR_BUFFER_RX == 1
            {
                ioutilsRX_CHARS_INTO_CIRCULAR_BUFFER_FROM_ISR(
                        pxTransferStruct,   /* The structure that contains the reference to the circular buffer. */
                        (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET),    /* While loop condition. */
                        USART_ReceiveData(USART1),         /* Register holding the received character. */
                        ulReceived,
                        xHigherPriorityTaskWoken);
            }
            #endif /* ioconfigUSE_UART_CIRCULAR_BUFFER_RX */
                break;

            case ioctlUSE_CHARACTER_QUEUE_RX:
            #if ioconfigUSE_UART_RX_CHAR_QUEUE == 1
            {
                size_t i = 1;
                ioutilsRX_CHARS_INTO_QUEUE_FROM_ISR(
                        pxTransferStruct,
                        i--,
                        USART_ReceiveData(USART1),
                        ulReceived,
                        xHigherPriorityTaskWoken);
            }
            #endif /* ioconfigUSE_UART_RX_CHAR_QUEUE */
                break;

            default:
                break;
            }
        }
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }

    if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET) {
        pxTransferStruct = pxTxTransferControlStructs[uxUARTNumber];
        if (pxTransferStruct != NULL) {
            switch (diGET_TRANSFER_TYPE_FROM_CONTROL_STRUCT(pxTransferStruct)) {
            case ioctlUSE_ZERO_COPY_TX:
            #if ioconfigUSE_UART_ZERO_COPY_TX == 1
            {
                iouitlsTX_SINGLE_CHAR_FROM_ZERO_COPY_BUFFER_FROM_ISR(
                        pxTransferStruct,
                        USART_SendData(USART1, ucChar),
                        xHigherPriorityTaskWoken);
            }
            #endif /* ioconfigUSE_UART_ZERO_COPY_TX */
                if (xHigherPriorityTaskWoken != pdTRUE)
                    USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
                break;

            case ioctlUSE_CHARACTER_QUEUE_TX:
            #if ioconfigUSE_UART_TX_CHAR_QUEUE == 1
            {
                size_t i = 1;
                ioutilsTX_CHARS_FROM_QUEUE_FROM_ISR(
                        pxTransferStruct,
                        i--,
                        USART_SendData(USART1, ucChar),
                        xHigherPriorityTaskWoken);
            }
            #endif /* ioconfigUSE_UART_TX_CHAR_QUEUE */
            if (xHigherPriorityTaskWoken != pdTRUE)
                USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
                break;

            default:
                /* This must be an error.  Force an assert. */
                configASSERT( xHigherPriorityTaskWoken );
                break;
            }
        }
        USART_ClearITPendingBit(USART1, USART_IT_TXE);
    }
    /* The ulReceived parameter is not used by the UART ISR. */
    (void) ulReceived;

    /* If xHigherPriorityTaskWoken is now equal to pdTRUE, then a context
    switch should be performed before the interrupt exists.  That ensures the
    unblocked (higher priority) task is returned to immediately. */
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
