#include "../uart.h"
#include <stm32f10x.h>
#include <stdio.h>

#define USART1_DR       (&(USART1->DR))
#define USART1_BaudRate 9600           
#define TxBufferSize1   1

uint8_t TxBuffer1[TxBufferSize1];

/**
  * @brief  Configures the USART clock and pins .
  * @param  None
  * @retval None
  */
void USART1_Configuration(uint32_t BaudRate)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);

  /* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /*  USART1 configuration */
  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure USART1 */
  USART_Init(USART1, &USART_InitStructure);
  /* Enable the DMA to transmit data */
  USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  
  /* Enable the USART1 */
  USART_Cmd(USART1, ENABLE);	
}

/**
  * @brief  Configures the DMA.
  * @param  None
  * @retval None
  */
static void DMA_Configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  /* Enable DMA clocks */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  /* USART1_Tx_DMA_Channel (triggered by USART1 Tx event) Config */
  DMA_DeInit(DMA1_Channel4);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)USART1_DR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer1;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = TxBufferSize1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
  
}

/**
  * @brief  Initial uart.
  * @param  None
  * @retval None
  */
void uart_init(void)
{   
  /* Configraue USART1 */
	USART1_Configuration(USART1_BaudRate);
  /* Configure USART1 TX DMA */        
	DMA_Configuration();
  /* Enable USART1 DMA TX Channel */
  DMA_Cmd(DMA1_Channel4, ENABLE);    
}

/**
  * @brief  uart send.
  * @param  ch: data to be send
  * @retval data send
  */
int uart_send(int ch)
{
    DMA_Cmd(DMA1_Channel4, DISABLE);
    TxBuffer1[0] = ch;
    DMA_SetCurrDataCounter(DMA1_Channel4, TxBufferSize1);
    DMA_Cmd(DMA1_Channel4, ENABLE);
    while(DMA_GetFlagStatus(DMA1_FLAG_TC4) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC4);

    return ch;

}

/**
  * @brief  redefine the function putchar in stdio.h.
  * @param  ch: data to be send
  * @retval data send
  */
PUTCHAR_PROTOTYPE
{
  uart_send(ch);
  return ch;
}
