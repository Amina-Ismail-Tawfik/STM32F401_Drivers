#include "GPIO.h"

#define TWO_BIT_MASK 0x00000003
#define PIN_MASK 2

typedef struct
{
	uint32 MODER;
    uint32 OTYPER;
    uint32 OSPEEDR;
    uint32 PUPDR;
    uint32 IDR;
    uint32 ODR;
    uint32 BSRR;
    uint32 LCKR;
    uint32 AFRL;
    uint32 AFRH;
}GPIO_t;


ErrorStatus_t GPIO_initPin (GPIO_cfg_t* PIN)
{
    ErrorStatus_t RetErrorStatus=NOK;
    /*if ((GPIO_t*)PIN->Port_Num!=GPIOA && (GPIO_t*)PIN->Port_Num!=GPIOB && (GPIO_t*)PIN->Port_Num != GPIOC)
    {
        RetErrorStatus=Parameter_Error;
    }*/

    ((GPIO_t*)(PIN->Port_Num))->MODER &=~ (TWO_BIT_MASK<<PIN_MASK*PIN->Pin_Num);
    ((GPIO_t*)(PIN->Port_Num))->MODER |= PIN->Mode<<(PIN_MASK*PIN->Pin_Num);
    ((GPIO_t*)(PIN->Port_Num))->OTYPER &=~ (1<<PIN->Pin_Num);
    ((GPIO_t*)(PIN->Port_Num))->OTYPER |= PIN->OutPut_Mode<<PIN->Pin_Num;
    ((GPIO_t*)(PIN->Port_Num))->OSPEEDR &= ~(TWO_BIT_MASK<<PIN_MASK*PIN->Pin_Num);
    ((GPIO_t*)(PIN->Port_Num))->OSPEEDR |= PIN->OutPut_Speed<<(PIN_MASK*PIN->Pin_Num);
    return RetErrorStatus;
}

ErrorStatus_t GPIO_setPinValue(void* PORT,u8 pin,u8 value)
{
    ErrorStatus_t RetErrorStatus = NOK;
    if (value==PIN_STAT_OFF)
    {
        ((GPIO_t*)PORT)->ODR &=~(1<<pin);
    }
    else if (value==PIN_STAT_ON)
    {
        ((GPIO_t*)PORT)->ODR |= (1<<pin);
    }
    return RetErrorStatus;
}

ErrorStatus_t GPIO_getPinValue(void* PORT,u8 pin,uint32* Pin_Stat)
{
    ErrorStatus_t RetErrorStatus = NOK;
    *Pin_Stat = ((GPIO_t*)PORT)->IDR & (1<<pin);
    return RetErrorStatus;
}


