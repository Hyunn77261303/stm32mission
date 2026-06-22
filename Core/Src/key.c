#include "key.h"
#include "gpio.h"
#include "tim.h"

static KeyEvent_t keyEvent = KEY_NONE;

/* 消抖 */
static uint8_t key1_last = 1;

void Key_Scan_Periodic(void)
{
    static uint16_t timer = 0;
    // 如果系统每 1ms 调用一次该函数
    if(++timer >= 10) 
    {
        Key_Scan(); 
        timer = 0;
    }
}

void Key_Scan(void)
{
	 keyEvent = KEY_NONE; 
    uint8_t key1_now = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
    uint8_t key2     = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);


    /* KEY1 */
    if(key1_last == 1 && key1_now == 0)
    {
        keyEvent = KEY1_SHORT;
    }

    key1_last = key1_now;

    /* KEY2 */
    static uint8_t key2_last = 1;

if(key2_last == 1 && key2 == 0)
{
    keyEvent = KEY2_PRESSING;
}
else if(key2_last == 0 && key2 == 1)
{
    keyEvent = KEY2_RELEASED;
}

key2_last = key2;
}

KeyEvent_t Key_GetEvent(void)
{
    KeyEvent_t temp = keyEvent;

    keyEvent = KEY_NONE;

    return temp;
}

