#include "Switch.h"
#include "GPIO.h"
extern const Switch_cfg_t switcheS [_SWITCH_NUM];
ErrorStatus_t Switch_init(void)
{
	GPIO_cfg_t Pin;
		Pin.GPIO_Mode=GPIO_MODE_INPUT;
		for (u8 itr=0;itr<_SWITCH_NUM;itr++)
		{
			Pin.GPIO_Port_Num=switcheS[itr].switch_Port;
			Pin.GPIO_Pin_Num=switcheS[itr].switch_Pin;
			Pin.GPIO_Pull=switcheS[itr].switch_Connection;
			GPIO_initPin(&Pin);
		}
}
