#include "LED.h"
#include "GPIO.h"
extern const LED_cfg_t LEDS [_LEDS_NUM];
ErrorStatus_t LED_init(void)
{
	ErrorStatus_t RetErrorStatus =NOK;
	GPIO_cfg_t Pin;
		Pin.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
		Pin.GPIO_OutPut_Speed=GPIO_HIGH_SPEED;
		for (u8 itr=0;itr<_LEDS_NUM;itr++)
		{
			Pin.GPIO_Port_Num=LEDS[itr].LED_Port;
			Pin.GPIO_Pin_Num=LEDS[itr].LED_Pin;
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
