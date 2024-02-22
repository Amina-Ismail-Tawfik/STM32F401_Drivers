#include "Switch.h"
#include "GPIO.h"
extern const Switch_cfg_t switcheS [_SWITCH_NUM];
ErrorStatus_t Switch_init(void)
{
	GPIO_cfg_t Pin;
		Pin.Mode=MODE_INPUT;
		for (u8 itr=0;itr<_SWITCH_NUM;itr++)
		{
			Pin.Port_Num=switcheS[itr].switch_Port;
			Pin.Pin_Num=switcheS[itr].switch_Pin;
			Pin.Input_Mode=switcheS[itr].switch_Connection;
			GPIO_initPin(&Pin);
		}
}
