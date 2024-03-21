#include "Switch.h"
#include "GPIO.h"
extern const Switch_cfg_t switcheS [_SWITCH_NUM];
uint8_t state[_SWITCH_NUM];
ErrorStatus_t Switch_init(void)
{
	ErrorStatus_t RetErrorStatus = NOK;
	GPIO_cfg_t Pin;
		Pin.GPIO_Mode=GPIO_MODE_INPUT;
		Pin.GPIO_OutPut_Speed=GPIO_LOW_SPEED;
		Pin.GPIO_AF=GPIO_AF_SYSTEM;

		for (uint8_t itr=0;itr<_SWITCH_NUM;itr++)
		{
			Pin.GPIO_Port_Num=switcheS[itr].switch_Port;
			Pin.GPIO_Pin_Num=switcheS[itr].switch_Pin;
			Pin.GPIO_Pull=switcheS[itr].switch_Connection;
			RetErrorStatus=GPIO_initPin(&Pin);
		}
		return RetErrorStatus;
}

ErrorStatus_t Switch_getKey(uint16_t Switch, uint8_t* Switch_State)
{
	ErrorStatus_t RetErrorStatus=NOK;
	if (Switch_State==0)
		{
			RetErrorStatus=NULL_PointerError;
		}
	else
	{
		switch(switcheS[Switch].switch_Connection)
		{
		case SWITCH_PULL_DOWN:
			*Switch_State=state[Switch];
			break;
		case SWITCH_PULL_UP:
			*Switch_State= !state[Switch];
			break;
		default:
			break;
		}
	}



	return RetErrorStatus;
}
void sw_runnable()
{
	static uint8_t curr=0;
	static uint32_t prev=0;
	static uint32_t counter[_SWITCH_NUM];

	uint32_t idx;
	for (idx=0;idx<_SWITCH_NUM;idx++)
	{
		GPIO_getPinValue(switcheS[idx].switch_Port,switcheS[idx].switch_Pin,&curr);
		if(curr==prev)
		{
			counter[idx]++;
		}
		else
			counter[idx]=0;
		if (counter[idx]==5)
		{
			state[idx]=curr;
			counter[idx]=0;
		}
	}


}








