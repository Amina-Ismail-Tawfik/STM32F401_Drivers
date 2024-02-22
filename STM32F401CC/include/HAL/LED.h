#ifndef LED_H
#define LED_H

#include "STD_TYPES.h"
#include "Errors.h"
#include "LED_cfg.h"

#define LED_ACTIVE_HIGH 0
#define LED_ACTIVE_LOW 1
#define LED_STAT_ON 1
#define LED_STAT_OFF 0

typedef struct{
	void* LED_Port;
	u8 LED_Pin;
	u8 LED_ActiveState;
	u8 LED_InitState;
}LED_cfg_t;

ErrorStatus_t LED_init(void);

ErrorStatus_t LED_SetStatus(uint32 LED,u8 LEDstatus);













#endif
