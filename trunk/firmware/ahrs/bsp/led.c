/**
 * @file led.c
 * @brief LED board support package
 */

#define NUM_LED     3

void led_init(void)
{
    led_hw_init(led);
    // led_off(led, state);
}

void led_on(int led)
{
}

void led_off(int led)
{
}
