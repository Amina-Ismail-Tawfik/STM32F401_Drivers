#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "Errors.h"
#include "LCD_cfg.h"
#include <sched.h>
typedef struct{
	void* LCD_Port;
	uint8_t LCD_Pin;
}LCD_cfg_t;
extern runnable_t LCD;
ErrorStatus_t LCD_initAsyn();
ErrorStatus_t LCD_getStateAsyn();
//ErrorStatus_t LCD_clearScreenAsyn();
//ErrorStatus_t LCD_setCursorPosAsyn();
ErrorStatus_t LCD_writeStringAsyn(char*string,uint8_t length);



#endif
