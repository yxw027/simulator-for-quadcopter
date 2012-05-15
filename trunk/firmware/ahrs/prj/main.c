/**
 * @file main.c
 * @brief The program entry
 */
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "uart.h"

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main()
{
  SystemInit();
  uart_init();

  while(1)
  {
  }
}
