#ifndef __KEY_H
#define __KEY_H

typedef enum 
{
	KEY_NONE = 0,
	KEY1_SHORT,
	KEY2_PRESSING,
	KEY2_RELEASED
}KeyEvent_t;

void Key_Scan(void);
void Key_Scan_Periodic(void);

KeyEvent_t Key_GetEvent(void);

#endif
