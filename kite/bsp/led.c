/**
* @file led.c
* @brief LED board support package
*/
#include "led.h"

#include "stm32f10x.h"

#if defined (__GCC__)
static GPIO_TypeDef* led_gpio_port[] = {
    [LED_GREEN] = GPIOB,
    [LED_YELLOW] = GPIOB,
    [LED_RED] = GPIOB,
};

static uint16_t led_gpio_pin[] = {
    [LED_GREEN] = GPIO_Pin_5,
    [LED_YELLOW] = GPIO_Pin_6,
    [LED_RED] = GPIO_Pin_7,
};
#elif defined (__CC_ARM)
static GPIO_TypeDef* led_gpio_port[] = {
	GPIOB,
	GPIOB,
	GPIOB,
	GPIOB,
};

static uint16_t led_gpio_pin[] = {
	GPIO_Pin_5,
	GPIO_Pin_6,
	GPIO_Pin_7,
	GPIO_Pin_3,
};
#endif

/**
* low level hardware initialization
*/
static void led_hw_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable GPIO Clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);

    // Remap PB3
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    //Initialize the LED pins as an output
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void led_init(void)
{
    led_hw_init();
    /* set default led status */
//    led_off(LED_GREEN);
//    led_off(LED_YELLOW);
//    led_off(LED_RED);
    led_off(LED_BLUE);
}

void led_on(led_t led)
{
    if (led < LED_MAX_NUM)
        GPIO_ResetBits(led_gpio_port[led], led_gpio_pin[led]);
}

void led_off(led_t led)
{
    if (led < LED_MAX_NUM)
        GPIO_SetBits(led_gpio_port[led], led_gpio_pin[led]);
}

void led_toggle(led_t led)
{
    if (led < LED_MAX_NUM) {
        led_gpio_port[led]->ODR ^= led_gpio_pin[led];
    }
}
