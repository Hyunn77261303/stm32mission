#ifndef __RGB_H
#define __RGB_H

typedef enum
{
	RGB_GREEN_ON = 0,
	RGB_RED_ON,
	RGB_GREEN_BREATH,
	RGB_OFF
}RGB_State_t;

void RGB_SetState(RGB_State_t state);
void RGB_BreathTask(void);

#endif
