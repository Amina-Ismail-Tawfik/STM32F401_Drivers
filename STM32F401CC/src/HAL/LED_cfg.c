/*
 * LED_cfg.c
 *
 *  Created on: Feb 20, 2024
 *      Author: adel
 */
#include "LED.h"
#include "GPIO.h"

const LED_cfg_t LEDS [_LEDS_NUM]=
{ [LED_ONE]={
				.LED_Port=GPIOA,
				.LED_Pin=GPIO_pin0,
				.LED_ActiveState=LED_ACTIVE_HIGH,
				.LED_InitState=LED_STAT_ON,
		}
};



