#include "bsp.h"

#include "led.h"
#include "uart.h"
#include "spi.h"
#include "mpu6000.h"

int bsp_init(void)
{
    int32_t retval = 0;

    sys_init();
    delay_init();
    led_init();
    uart_init();
    spi_init();
    retval = mpu6000_init();
    if (retval < 0) {
        while (1)
            led_on(LED_BLUE);
    }
    EXTI3_Config();

    return retval;
}
