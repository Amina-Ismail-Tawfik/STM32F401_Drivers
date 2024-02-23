/*
 * This file initializes and controls LEDs using GPIO pins.
 */

#include "LED.h"
#include "GPIO.h"

/* External declaration of LED configuration array */
extern const LED_cfg_t LEDS[_LEDS_NUM];


ErrorStatus_t LED_init(void)
{
    ErrorStatus_t RetErrorStatus = NOK;
    GPIO_cfg_t Pin;

    /* Configure GPIO pins for LEDs */
    Pin.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
    Pin.GPIO_OutPut_Speed = GPIO_HIGH_SPEED;
    Pin.GPIO_Pull = GPIO_NOPULL;
    Pin.GPIO_AF = GPIO_AF_SYSTEM;

    /* Initialize each LED */
    for (u8 itr = 0; itr < _LEDS_NUM; itr++)
    {
        Pin.GPIO_Port_Num = LEDS[itr].LED_Port;
        Pin.GPIO_Pin_Num = LEDS[itr].LED_Pin;
        RetErrorStatus = GPIO_initPin(&Pin);
    }

    return RetErrorStatus;
}

ErrorStatus_t LED_SetStatus(uint16 LED, u8 LED_STAT)
{
    ErrorStatus_t RetErrorStatus = NOK;

    if(LED > _LEDS_NUM)
    {
    	RetErrorStatus = ParameterError;
    }
    else if(LED_STAT>1)
    {
    	RetErrorStatus = ParameterError;
    }
    else
    {
    	RetErrorStatus = GPIO_setPinValue(LEDS[LED].LED_Port, LEDS[LED].LED_Pin, LEDS[LED].LED_ActiveState ^ LED_STAT);

    }
    return RetErrorStatus;
}

