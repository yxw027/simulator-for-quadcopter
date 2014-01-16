/**
 * @file uart.h
 * @brief UART interface
 */
#ifndef _UART_H
#define _UART_H

/**
 * @addtogroup kite
 * @}
 */

/**
 * @addtogroup BSP
 * @{
 */

#define USART1_IRQHandler usart1_irq_hander
/**
 * @brief Initialize UART ports
 *
 * @param None
 * @return None
 */
void uart_init(void);

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/** @} */

/** @} */

#endif /* _UART_H */
