gyro_calibration(struct gyro_bias_t *bias)
{
    int buf_size = sizeof(gyro_buf) / 4;
    
    bias->gyro_bias_x = gyro_buf_x / buf_size;
    bias->gyro_bias_y = gyro_buf_y / buf_size;
    bias->gyro_bias_z = gyro_buf_z / buf_size;
}

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
    RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM1, ENABLE);

    /* Enable the TIM1 global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_IRQn;
    NVIC_Init(&NVIC_InitStructure);

    /* Configure TIM1 to generate interrupt each 2.5ms(400HZ) */
    TIM_TimeBaseStructure.TIM_Period = 2500;
    TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / 1000000) - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    /* TIM1 IT enable */
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

    /* TIM1 enable counter */
    TIM_Cmd(TIM1, ENABLE);
}
