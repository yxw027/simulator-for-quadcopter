/**
 * @file stm32f10x_led.c
 * @brief LED support
 */

#include <bsp/led.h>

#define LED_NUM_BASE    0
#define LED_NUM_1       1
#define LED_NUM_2       2
#define LED_NUM_3       3
#define LED_NUM_MAX     4


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

void led_on(int led)
{
    int i = led;
    if ((i < LED_NUM_BASE) || (i > LED_NUM_MAX))
        return;

    switch (i) {
    case LED_NUM_1:
        GPIO_ResetBits(GPIOA, GPIO_Pin_4);
        break;
    case LED_NUM_2:
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
        break;
    case LED_NUM_3:
        break;
    default:
        break;
    }

    return;
}

void led_off(int led)
{
    int i = led;
    if ((i < LED_NUM_BASE) || (i > LED_NUM_MAX))
        return;

    switch (i) {
    case LED_NUM_1:
        GPIO_SetBits(GPIOA, GPIO_Pin_4);
        break;
    case LED_NUM_2:
        GPIO_SetBits(GPIOA, GPIO_Pin_4);
        break;
    case LED_NUM_3:
        break;
    default:
        break;
    }

    return;        
}

void led_toogle(int led)
{
    int i = led;
    if ((i < LED_NUM_BASE) || (i > LED_NUM_MAX))
        return;

    switch (i) {
    case LED_NUM_1:
        uint8_t val = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4);
        GPIO_WriteBit(GPIOA, GPIO_Pin_4, (1 - val));
        break;
    case LED_NUM_2:
        uint8_t val = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_5);
        GPIO_WriteBit(GPIOA, GPIO_Pin_5, (1 - val));    
        break;
    case LED_NUM_3:
        break;
    default:
        break;
    }

    return;
}
