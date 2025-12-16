#include "..\Inc\init.h"

extern uint16_t left_encoder_ticks;
extern uint16_t right_encoder_ticks;

extern uint32_t left_delay_counter;
extern uint32_t right_delay_counter;
extern uint16_t button_delay_counter;

extern bool status_button;

void SysTick_Handler(void)
{
    if (left_delay_counter > 0)
    {
        left_delay_counter--;
    }
    if (right_delay_counter > 0)
    {
        right_delay_counter--;
    }
    if (button_delay_counter > 0)
    {
        button_delay_counter--;
    }
}


void EXTI15_10_IRQHandler(void)
{
    // Обработчик прерываний с правого энкодера PC12
    if (READ_BIT(EXTI->PR, EXTI_PR_PR12))
    {
        if (right_delay_counter == 0)
        {
            right_encoder_ticks++;
            right_delay_counter = 60;
        }
        SET_BIT(EXTI->PR, EXTI_PR_PR12);
    }

    // Обработчик прерываний с кнопки PC13
    if (READ_BIT(EXTI->PR, EXTI_PR_PR13))
    {
        if (((READ_BIT(GPIOC->IDR, GPIO_IDR_ID13) != 0)) && (button_delay_counter == 0))
        {
            button_delay_counter = 100;
            status_button = !status_button;
        }
        SET_BIT(EXTI->PR, EXTI_PR_PR13);
    }
}

    // Обработчик прерываний с левого энкодера PC8
    void EXTI9_5_IRQHandler(void)
    {
        SET_BIT(EXTI->PR, EXTI_PR_PR12);
        if (right_delay_counter == 0)
        {
            right_encoder_ticks++;
            right_delay_counter = 60;
        }
    }
