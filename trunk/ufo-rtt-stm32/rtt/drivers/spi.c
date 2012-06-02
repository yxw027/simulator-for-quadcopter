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

    /* Disable the JTAG Port JTAG-DP & Enable SWJ-DP Port SWJ-DP */
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    /* Configure NSS, SCK and MOSI pins as Alternate Function Push Pull */
    GPIO_InitStructure.GPIO_Pin = /* SPI_MASTER_PIN_NSS | */SPI_MASTER_PIN_SCK | SPI_MASTER_PIN_MOSI;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);

    /* Configure MISO pin as Input Floating */
    GPIO_InitStructure.GPIO_Pin = SPI_MASTER_PIN_MISO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);
    
        GPIO_InitStructure.GPIO_Pin = SPI_MASTER_PIN_CS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
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
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI_MASTER, &SPI_InitStructure);

    /* Enable SPI_MASTER */
    SPI_Cmd(SPI_MASTER, ENABLE);
}

u8 SPI_WriteByte(SPI_TypeDef *SPIx, u8 data)
{
    u8 Data = 0;

    /* Wait until the transmit buffer is empty */
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
    /* Send the byte */
    SPI_I2S_SendData(SPIx, data);

    /* Wait until a data is received */
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
    /* Get the received data */
    Data = SPI_I2S_ReceiveData(SPIx);

    /* Return the shifted data */
    return Data;
}
