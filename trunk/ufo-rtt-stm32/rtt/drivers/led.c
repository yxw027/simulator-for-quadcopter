/**
 * @file led.c
 * @brief LED support
 */
#include <stm32f10x.h>

#include "led.h"


static void RCC_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}

static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void led_init(void)
{
    RCC_Configuration();
    GPIO_Configuration();
}

static void hw_led_on(int led)
{
    switch (led) {
    case 0:
        GPIO_SetBits(GPIOA, GPIO_Pin_4);
        break;
    case 1:
        GPIO_SetBits(GPIOA, GPIO_Pin_5);
        break;
    default:
        break;
    }
}

static void hw_led_off(int led)
{
    switch (led) {
    case 0:
        GPIO_ResetBits(GPIOA, GPIO_Pin_4);
        break;
    case 1:
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
        break;
    default:
        break;
    }
}

static void hw_led_toggle(int led)
{
    switch (led) {
    case 0:
      GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4)));
      break;
    case 1:
      GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_5)));
    default:
        break;
    }
}

void led_on(int led)
{
    hw_led_on(led);
}

void led_off(int led)
{
    hw_led_off(led);
}

void led_toggle(int led)
{
    hw_led_toggle(led);
}

void leds_on(int leds)
{
    int i;

    for (i = 0; i < LED_NUM_MAX; i++) {
        if (leds & (1 << i))
            hw_led_on(i);
    }
}
