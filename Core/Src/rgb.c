#include "rgb.h"
#include "gpio.h"
#include "tim.h"

static RGB_State_t currentState;

static int16_t pwm = 0;
static int8_t dir = 1;

void RGB_SetState(RGB_State_t state)
{
    currentState = state;
	
	switch(currentState)
    {
        case RGB_GREEN_ON:

            __HAL_TIM_SET_COMPARE(&htim2,
                                  TIM_CHANNEL_1,
                                  1000);   

            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET); // ºìµÆÃð
            break;
				
				
				case RGB_RED_ON:

            __HAL_TIM_SET_COMPARE(&htim2,
                                  TIM_CHANNEL_1,
                                  0);     // ÂÌµÆÃð

            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);   // ºìµÆÁÁ
            break;
				
				
				case RGB_GREEN_BREATH:
					HAL_GPIO_WritePin(GPIOA,
                      GPIO_PIN_8,
                      GPIO_PIN_RESET);   // ºìµÆÃð
            pwm = 0;
            dir = 1;
            break;
				
				case RGB_OFF:
					  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
            __HAL_TIM_SET_COMPARE(&htim2,
                                 TIM_CHANNEL_1,
                                 0);  //¶¼²»ÁÁ
    }
}
void RGB_BreathTask(void)
{
    static uint32_t lastTick = 0;

    if(currentState != RGB_GREEN_BREATH)
        return;

    if(HAL_GetTick() - lastTick < 10)
        return;

    lastTick = HAL_GetTick();

    pwm += dir * 10;

    if(pwm >= 1000)
    {
        pwm = 1000;
        dir = -1;
    }

    if(pwm <= 0)
    {
        pwm = 0;
        dir = 1;
    }

    __HAL_TIM_SET_COMPARE(&htim2,
                          TIM_CHANNEL_1,
                          pwm);
}
