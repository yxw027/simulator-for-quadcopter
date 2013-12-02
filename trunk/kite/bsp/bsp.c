#include "bsp.h"

#include "led.h"
#include "uart.h"

void bsp_init(void)
{
    led_init();
    uart_init();
}
