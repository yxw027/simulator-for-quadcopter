#include <stm32f10x.h>

#include "sys.h"

static void RCC_Configuration(void)
{
    /* Enable DMA1 clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}

void sys_init(void)
{
    /* RCC Configuration */
    RCC_Configuration();
}
