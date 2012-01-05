/**
 * @file led.c
 * @brief LED support
 */

void led_init(int led, enum led_state state)
{
    led_hw_init(led);
    led_set(led, state);
}

void led_set(int led, enum led_state state)
{
    switch (state) {
    case LED_ON:
        led_hw_on(led);
        break;
    case LED_OFF:
        led_hw_off(led);
        break;
    case LED_TOGGLED:
        led_hw_toggled(led);
        break;
    default:
        break;
}