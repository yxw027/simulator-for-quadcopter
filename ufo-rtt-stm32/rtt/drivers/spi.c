#include <stm32f10x.h>

#include "spi.h"

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
static void RCC_Configuration(void)
{
    /* Enable SPI_SPI_MASTER clock and GPIO clock */
    RCC_APB2PeriphClockCmd(SPI_MASTER_GPIO_CLK | SPI_MASTER_CLK, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure NSS, SCK and MOSI pins as Alternate Function Push Pull */
    GPIO_InitStructure.GPIO_Pin = SPI_MASTER_PIN_NSS | SPI_MASTER_PIN_SCK | SPI_MASTER_PIN_MOSI;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);

    /* Configure MISO pin as Input Floating */
    GPIO_InitStructure.GPIO_Pin = SPI_MASTER_PIN_MISO;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);    
}

void spi_init(void)
{
    SPI_InitTypeDef SPI_InitStructure;

    RCC_Configuration();

    GPIO_Configuration();

    /* SPI_MASTER configuration */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI_MASTER, &SPI_InitStructure);

    /* Enable SPI_MASTER */
    SPI_Cmd(SPI_MASTER, ENABLE);    
}
