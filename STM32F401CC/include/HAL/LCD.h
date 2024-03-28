#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "Errors.h"
#include "LCD_cfg.h"
#include <sched.h>

#define FIRST_LINE	0
#define SECOND_LINE	1

typedef struct{
	void* LCD_Port;
	uint8_t LCD_Pin;
}LCD_cfg_t;


ErrorStatus_t LCD_initAsyn();
ErrorStatus_t LCD_writeStringAsyn(const char*string,uint8_t length);
ErrorStatus_t LCD_clearScreenAsyn();
ErrorStatus_t LCD_setCursorPosAsyn(uint8_t posX,uint8_t posY);
ErrorStatus_t LCD_getState(uint8_t * state);


#endif
