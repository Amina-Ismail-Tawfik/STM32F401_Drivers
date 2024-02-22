#include "LED.h"
#include "GPIO.h"
extern const LED_cfg_t LEDS [_LEDS_NUM];
ErrorStatus_t LED_init(void)
{
	ErrorStatus_t RetErrorStatus =NOK;
	GPIO_cfg_t Pin;
		Pin.Mode=MODE_OUTPUT;
		Pin.OutPut_Mode=OPT_PP;
		Pin.OutPut_Speed=HIGH_SPEED;
		for (u8 itr=0;itr<_LEDS_NUM;itr++)
		{
			Pin.Port_Num=LEDS[itr].LED_Port;
			Pin.Pin_Num=LEDS[itr].LED_Pin;
			GPIO_initPin(&Pin);
		}
		return RetErrorStatus;
}
ErrorStatus_t LED_SetStatus(uint32 LED,u8 LEDstatus)
{
	ErrorStatus_t RetErrorStatus =NOK;
	GPIO_setPinValue(LEDS[LED].LED_Port,LEDS[LED].LED_Pin,LEDS[LED].LED_ActiveState^LEDstatus);
	return RetErrorStatus;
}
