#include "Switch.h"
#include "GPIO.h"
extern const Switch_cfg_t switcheS [_SWITCH_NUM];
ErrorStatus_t Switch_init(void)
{
	ErrorStatus_t RetErrorStatus = NOK;
	GPIO_cfg_t Pin;
		Pin.GPIO_Mode=GPIO_MODE_INPUT;
		Pin.GPIO_OutPut_Speed=GPIO_LOW_SPEED;
		Pin.GPIO_AF=GPIO_AF_SYSTEM;

		for (u8 itr=0;itr<_SWITCH_NUM;itr++)
		{
			Pin.GPIO_Port_Num=switcheS[itr].switch_Port;
			Pin.GPIO_Pin_Num=switcheS[itr].switch_Pin;
			Pin.GPIO_Pull=switcheS[itr].switch_Connection;
			RetErrorStatus=GPIO_initPin(&Pin);
		}
		return RetErrorStatus;
}

ErrorStatus_t Switch_getKey(uint16 Switch, u8* Switch_State)
{
	ErrorStatus_t RetErrorStatus=NOK;
	if (Switch_State==0)
		{
			RetErrorStatus=NULL_PointerError;
		}
	else
	{
		RetErrorStatus=GPIO_getPinValue(switcheS[Switch].switch_Port,switcheS[Switch].switch_Pin,Switch_State);
		switch(switcheS[Switch].switch_Connection)
		{
		case SWITCH_PULL_DOWN:
			break;
		case SWITCH_PULL_UP:
			*Switch_State= !Switch_State;
			break;
		default:
			break;
		}
	}



	return RetErrorStatus;
}
