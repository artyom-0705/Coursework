#include "..\Inc\init.h"

void SysTick_Init(void)
{
    CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk); // выключим счетчик
    SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk); // Разрешаем прерывание по системному таймеру
    SET_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk); // источник тактирования AHB без делителя
    MODIFY_REG(SysTick->LOAD, SysTick_LOAD_RELOAD_Msk, 95999 << SysTick_LOAD_RELOAD_Pos); // Значение с которого начинается счёт, эквивалентное 1 кГц 
    MODIFY_REG(SysTick->VAL, SysTick_VAL_CURRENT_Msk, 95999 << SysTick_VAL_CURRENT_Pos);  // Очистка поля
    SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);                                      // Включим счетчик
}



void ITR_Init(void)
{
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN); //Включение тактирования периферии SYSCFG 

    // Настройка прерываний на PC12 (правый энкодер)
    MODIFY_REG(SYSCFG->EXTICR[3], SYSCFG_EXTICR4_EXTI12_Msk, 
    SYSCFG_EXTICR4_EXTI12_PC); //Настройка мультиплексора на вывод линии прерывания EXTI12 на PC12 

    // настройка EXTI регистров
    SET_BIT(EXTI->IMR, EXTI_IMR_MR12); //Настройка маскирования 12 линии 
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR12); //Настройка детектирования нарастающего фронта 12 линии 
    //SET_BIT(EXTI->FTSR, EXTI_FTSR_TR12); //Настройка детектирования спадающего фронта 12 линии 
    NVIC_SetPriority(EXTI15_10_IRQn, 
    NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0)); //Установка 0 приоритета прерывания для вектора EXTI15_10 
    NVIC_EnableIRQ(EXTI15_10_IRQn); //Включение прерывания по вектору EXTI15_10
    
    //==================================================================================================

    // Настройка прерываний на PC8 (левый энкодер)
    MODIFY_REG(SYSCFG->EXTICR[2], SYSCFG_EXTICR3_EXTI8_Msk, 
    SYSCFG_EXTICR3_EXTI8_PC); //Настройка мультиплексора на вывод линии прерывания EXTI8 на PC8 

    // настройка EXTI регистров
    SET_BIT(EXTI->IMR, EXTI_IMR_MR8); //Настройка маскирования 8 линии 
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR8); //Настройка детектирования нарастающего фронта 8 линии 
    //SET_BIT(EXTI->FTSR, EXTI_FTSR_TR12); //Настройка детектирования спадающего фронта 8 линии 
    NVIC_SetPriority(EXTI9_5_IRQn, 
    NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0)); //Установка 0 приоритета прерывания для вектора EXTI9_5 
    NVIC_EnableIRQ(EXTI9_5_IRQn); //Включение прерывания по вектору EXTI15_10

    //==================================================================================================

    // Настройка прерываний на PC13 (кнопка)
    MODIFY_REG(SYSCFG->EXTICR[3], SYSCFG_EXTICR4_EXTI13_Msk, 
    SYSCFG_EXTICR4_EXTI13_PC); //Настройка мультиплексора на вывод линии прерывания EXTI13 на PC13 

    // настройка EXTI регистров
    SET_BIT(EXTI->IMR, EXTI_IMR_MR13); //Настройка маскирования 13 линии 
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR13); //Настройка детектирования нарастающего фронта 13 линии 
    //SET_BIT(EXTI->FTSR, EXTI_FTSR_TR13); //Настройка детектирования спадающего фронта 13 линии 
    NVIC_SetPriority(EXTI15_10_IRQn, 
    NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0)); //Установка 0 приоритета прерывания для вектора EXTI15_10 
    NVIC_EnableIRQ(EXTI15_10_IRQn); //Включение прерывания по вектору EXTI15_10
    
}



void RCC_Init(void)
{
     /* Предварительная очистка регистров RCC */ 
    MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 0x80UL); 
    CLEAR_REG(RCC->CFGR); 
    while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET); 
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON); 
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RESET); 
    CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON); 
    while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != RESET); 
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP); 
 
    /* Настройка главного регистра RCC */ 
    SET_BIT(RCC->CR, RCC_CR_HSION);                              
    while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == RESET);
 
    /*Настройка регистра PLLCFGR*/
    CLEAR_REG(RCC->PLLCFGR);                                        // Очищаем регистр PLLCFGR
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_HSI);                  // Источник тактирования HSI
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLM_3);                      // Деление источника тактирования на 8
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLN_5); // Настрока умножения на 96
    CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_0);                    // Делитель для выхода PLL(PLLCLK) на 2
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ_2);                      // Делитель для USB на 15

    /*Настройка регистра CFGR*/
    SET_BIT(RCC->CFGR, RCC_CFGR_SW_PLL);                            // Источник системного тактирования -> выход PLL 96мгц
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_HPRE_DIV1);                       // Делитель AHB1 -> 1
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE1_DIV2);                        // Делитель APB1 -> 2 (48 МГц)
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE2_DIV1);                        // Делитель APB2 -> 1 (96 МГц) 
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_MCO2);  
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_MCO2_0 | RCC_CFGR_MCO2_1);        // Выход MCO2 -> Sysclk
    SET_BIT(RCC->CFGR, RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1);    // Делитель для MCO2 -> 4

    /*Настрйока частоты FLASH-памяти*/
    SET_BIT(FLASH->ACR, FLASH_ACR_LATENCY_3WS);

    /*Включение блока PLL*/
    SET_BIT(RCC->CR, RCC_CR_PLLON);
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == RESET);

}


// ШИМ ЧАСТОТОЙ 50ГЦ
void TIM1_PWM_Init(void)
{
    // Включение тактирования периферии
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);   // Включаем тактирование порта A (шина AHB1)
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);    // Включаем тактирование TIM1 (шина APB2)

    // Настройка выводов GPIO для PA8 и PA9
    // Настраиваем PA8 и PA9 на альтернативную функцию (режим 10)
    MODIFY_REG(GPIOA->MODER,
               GPIO_MODER_MODE8 | GPIO_MODER_MODE9,
               GPIO_MODER_MODE8_1 | GPIO_MODER_MODE9_1);

    // Назначаем альтернативную функцию 1 (TIM1) для PA8 и PA9
    MODIFY_REG(GPIOA->AFR[1],
               GPIO_AFRH_AFSEL8 | GPIO_AFRH_AFSEL9,
               1UL << GPIO_AFRH_AFSEL8_Pos | 1UL << GPIO_AFRH_AFSEL9_Pos);

    // Настройка таймера
    CLEAR_BIT(TIM1->CR1, TIM_CR1_CEN);            // Останавливаем таймер перед настройкой

    // Настройка частоты ШИМ: 96 МГц / (PSC+1) / (ARR+1) = 96 МГц / 6 / 1000 = 16 кГц
    MODIFY_REG(TIM1->PSC, TIM_PSC_PSC_Msk, 5UL);  // Предделитель = 6 (PSC = 5)
    MODIFY_REG(TIM1->ARR, TIM_ARR_ARR_Msk, 999UL);// Период = 1000 (ARR = 999) → частота 16 кГц

    SET_BIT(TIM1->CR1, TIM_CR1_ARPE);             // Включаем буферизацию регистра ARR (preload)

    // Настройка режима ШИМ для каналов 1 и 2
    // Канал 1 (PA8): ШИМ режим 1 (110) + буферизация CCR1
    MODIFY_REG(TIM1->CCMR1,
               TIM_CCMR1_OC1M_Msk | TIM_CCMR1_OC1PE_Msk,
               (6UL << TIM_CCMR1_OC1M_Pos) | TIM_CCMR1_OC1PE);

    // Канал 2 (PA9): ШИМ режим 1 (110) + буферизация CCR2
    MODIFY_REG(TIM1->CCMR1,
               TIM_CCMR1_OC2M_Msk | TIM_CCMR1_OC2PE_Msk,
               (6UL << TIM_CCMR1_OC2M_Pos) | TIM_CCMR1_OC2PE);

    // Включение выходов для каналов 1 и 2
    SET_BIT(TIM1->BDTR, TIM_BDTR_MOE);            // Включаем главный выход (обязательно для TIM1)
    
    // Включаем каналы 1 и 2 ШИМ
    SET_BIT(TIM1->CCER, TIM_CCER_CC1E | TIM_CCER_CC2E);

    // Установка начальной коэффициента заполнения (0%) только для каналов 1 и 2
    MODIFY_REG(TIM1->CCR1, TIM_CCR1_CCR1_Msk, 0UL);  // Двигатель 1 (PA8): CCR1 = 0 (0%)
    MODIFY_REG(TIM1->CCR2, TIM_CCR2_CCR2_Msk, 0UL);  // Двигатель 2 (PA9): CCR2 = 0 (0%)

    // Активация настроек и запуск таймера
    SET_BIT(TIM1->EGR, TIM_EGR_UG);               // Генерируем update event (загружаем PSC и ARR)
    SET_BIT(TIM1->CR1, TIM_CR1_CEN);              // Запускаем таймер
}



void Set_PWM_PA8_DutyCycle(uint8_t percent)
{
    if (percent > 100)                                      // Ограничение максимального значения
    {
        percent = 100;
    }
    
    uint32_t ccr1_value = (TIM1->ARR * percent) / 100;      // Перевод процентов в значение CCR1
    MODIFY_REG(TIM1->CCR1, TIM_CCR1_CCR1_Msk, ccr1_value);  // Устанавливаем новое значение в регистр CCR1
}


void Set_PWM_PA9_DutyCycle(uint8_t percent)
{
    if (percent > 100)                                      // Ограничение максимального значения
    {
        percent = 100;
    }
    
    uint32_t ccr2_value = (TIM1->ARR * percent) / 100;      // Перевод процентов в значение CCR2
    MODIFY_REG(TIM1->CCR2, TIM_CCR2_CCR2_Msk, ccr2_value);  // Устанавливаем новое значение в регистр CCR2
}