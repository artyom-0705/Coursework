
#include "init.h"  // Подключаем заголовочный файл с объявлениями функций
#include "utils.h"

uint8_t pwm_state_pa8 = 0;
uint8_t pwm_state_pa9 = 0;
uint16_t left_encoder_ticks = 0;
uint16_t right_encoder_ticks = 0;
uint32_t left_delay_counter = 0;
uint32_t right_delay_counter = 0;

uint16_t button_delay_counter = 0;
bool status_button = 0;

int main(void)
{
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN);
    SET_BIT(GPIOC->PUPDR, GPIO_PUPDR_PUPDR12_0);
    // Инициализируем прерывания
    ITR_Init();
    // Инициализируем тактирование системы (RCC)
    RCC_Init();            // Настраивает тактовую частоту 96 МГц
    
    // Инициализируем SysTick (опционально, для задержек)
    SysTick_Init();        // Настраивает системный таймер на 1 кГц
    
    // Инициализируем ШИМ
    TIM1_PWM_Init();       // Настраивает TIM1 для ШИМ на PA8 и PA9
    
    // Теперь можно использовать функции установки коэффициента заполнения
    Set_PWM_PA8_DutyCycle(75);    // Установить 0% на PA8
    Set_PWM_PA9_DutyCycle(75);    // Установить 0% на PA9
    while(1)
    {
    }
}