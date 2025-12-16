#include "init.h"


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


// Настройка драйвера (IN3 и IN4)
 void left_wheel_direction(uint8_t direction)
 {
    if (direction == 0)
    {
        // Остановка колеса
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR10);
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR4);
    }
    if (direction == 1)
    {
        // Колесо движется вперед
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS10);
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR4);
    }
    if (direction == 2)
    {
        // Колесо движется назад
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR10);
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS4);
    }
 }

 // Настройка драйвера (IN1 и IN2)
  void right_wheel_direction(uint8_t direction)
 {
    if (direction == 0)
    {
        // Остановка колеса
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR5);
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR3);
    }
    if (direction == 1)
    {
        // Колесо движется вперед
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS5);
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR3);
    }
    if (direction == 2)
    {
        // Колесо движется назад
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR5);
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS3);
    }
 }