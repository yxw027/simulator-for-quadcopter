#include "bsp.h"

#include "led.h"
#include "uart.h"
#include "spi.h"
#include "mpu6000.h"

int bsp_init(void)
{
    int retval = 0;

    led_init();
    uart_init();
    spi_init();
    retval = mpu6000_init();
    if (retval < 0)
        led_on(LED_BLUE);

    return retval;
}
