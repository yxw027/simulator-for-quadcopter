#ifndef _SPI_H
#define _SPI_H

#define SPI_MASTER                  SPI1
#define SPI_MASTER_CLK              RCC_APB2Periph_SPI1
#define SPI_MASTER_GPIO             GPIOA
#define SPI_MASTER_GPIO_CLK         RCC_APB2Periph_GPIOA  
#define SPI_MASTER_PIN_NSS          GPIO_Pin_4
#define SPI_MASTER_PIN_SCK          GPIO_Pin_5
#define SPI_MASTER_PIN_MISO         GPIO_Pin_6
#define SPI_MASTER_PIN_MOSI         GPIO_Pin_7

#endif /* _SPI_H */