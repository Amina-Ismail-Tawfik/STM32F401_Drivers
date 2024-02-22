#include "Switch.h"
#include "GPIO.h"

const Switch_cfg_t switcheS [_SWITCH_NUM]=
{ [switch_ONE]={
				.switch_Port=GPIOA,
				.switch_Pin=pin0,
				.switch_Connection=PULL_DOWN,
		}
};
