#include <stm32f10x.h>

#include "gyroscope.h"

#if SENSOR_GYROSCOPE == L3G4200D
  #include "l3g4200D_driver.h"
#endif

#define L3G4200D_Enable()   GPIO_ResetBits(GPIOA, GPIO_Pin_15)
#define L3G4300D_Disable()  GPIO_SetBits(GPIOA, GPIO_Pin_15)

#if SENSOR_GYROSCOPE == L3G4200D
void l3g4200d_init()
{
    //set the ODR and Bandwith
    SetODR(ODR_100Hz_BW_12_5);

    //enable all axis  
    SetAxis(X_ENABLE | Y_ENABLE | Z_ENABLE);

    //set the fullscale
    SetFullScale(FULLSCALE_250);

    //set sensor mode
    SetMode(NORMAL);
}
#endif

/**
 * @brief TIM1 is used to generate a periodic interrupt.
 * @param None
 * @return None
 */
static void TIM1_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    /* TIM1 clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    /* Enable the TIM1 Update Interrupt */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_Init(&NVIC_InitStructure);

    /* Configure TIM1 to generate interrupt each 2.5ms(400HZ) */
    TIM_TimeBaseStructure.TIM_Period = 2500;
    TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / 1000000) - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_ClearFlag(TIM1, TIM_FLAG_Update);

    /* TIM1 IT enable */
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

    /* TIM1 enable counter */
    TIM_Cmd(TIM1, ENABLE);
}

void gyro_init()
{
#if SENSOR_GYROSCOPE == L3G4200D
    l3g4200d_init();
#endif

    TIM1_Config();
}
