#include <stdbool.h>

#include "..\..\CMSIS\Devices\STM32F4xx\Inc\STM32F411xE\stm32f411xe.h"
#include "..\..\CMSIS\Devices\STM32F4xx\Inc\stm32f4xx.h"

#include "it_handlers.h"

void ITR_Init(void);
void SysTick_Init(void);
void RCC_Init(void);
void TIM1_PWM_Init(void);
void Set_PWM_PA8_DutyCycle(uint8_t percent);
void Set_PWM_PA9_DutyCycle(uint8_t percent);