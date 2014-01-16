/**
 * @file uart.c
 * @brief UART modules implementation
 */

#include <stdio.h>

#include <stm32f10x.h>

#include "uart.h"

/**
 * @addtogroup kite
 * @{
 */

/**
 * @addtogroup BSP
 * @{
 */

static struct fifo fifo_tx;
static uint8_t buffer[8];

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
    GPIO_InitTypeDef GPIO_InitStructure;

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
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    /* Enable the USART1 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void uart_hw_init()
{
    USART_InitTypeDef USART_InitStructure;
    //USART_ClockInitTypeDef USART_ClockInitStructure;
    /* System Clocks Configuration */
    RCC_Configuration();

    /* NVIC configuration */
    // NVIC_Configuration();

    /* Configure the GPIO ports */
    GPIO_Configuration();

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

/*
    USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
        USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
        USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
        USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
        USART_ClockInit(USART1, &USART_ClockInitStructure);
*/
    /* USART1 configuration */
    USART_Init(USART1, &USART_InitStructure);

    /* Enable USART1 */
    USART_Cmd(USART1, ENABLE);

    fifo_init(&fifo_tx, buffer, sizeof(buffer));
}

void uart_init(void)
{
    uart_hw_init();
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

/**
 * Send buffer from usart via interrupt
 *
 * @return bytes has sent
 */
uint8_t uart_write(uint_t id, uint8_t *buf, uint8_t len)
{
    uint8_t retval = -1;
    USART_TypeDef *USARTx;
    switch (id) {
    case 0:
        USARTx = USART1;
        break;
    default:
        config_ASSERT(USARTx);
        break;
    }

    retval = fifo_write(fifo_tx, buf, len);
    if (retval > 0)
        USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);

    return retval;
}

void usart1_irq_handler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET) {
        /* get one byte from fifo */
        uint8_t retval = fifo_read(fifo_tx, &ch, 1);
        if (retval == 1) {
            USART_SendData(USART1, ch);
        } else {
            USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
        }

        USART_ClearITPendingBit(USART1, USART_IT_TXE);
    }
}
/** @} */

/** @} */
