#ifndef GPIO_H
#define GPIO_H
#include "STD_TYPES.h"
#include "Errors.h"

#define GPIOA_BASE_ADDRESS        0x40020000
#define GPIOB_BASE_ADDRESS        0x40020400
#define GPIOC_BASE_ADDRESS        0x40020800
#define GPIOD_BASE_ADDRESS        0x40020C00
#define GPIOE_BASE_ADDRESS        0x40021000
#define GPIOH_BASE_ADDRESS        0x40021C00

#define GPIOA     (void *)GPIOA_BASE_ADDRESS
#define GPIOB     (void *)GPIOB_BASE_ADDRESS
#define GPIOC     (void *)GPIOC_BASE_ADDRESS
#define GPIOD     (void *)GPIOD_BASE_ADDRESS
#define GPIOE     (void *)GPIOE_BASE_ADDRESS
#define GPIOH     (void *)GPIOH_BASE_ADDRESS

#define MODE_INPUT      0x00000000
#define MODE_OUTPUT     0x00000001
#define MODE_AF         0x00000002
#define MODE_ANALOG     0x00000003

#define OPT_PP          0
#define OPT_OD          1

#define IPT_PD			2
#define IPT_PU			1

#define LOW_SPEED           0
#define MEDIUM_SPEED        1
#define HIGH_SPEED          2
#define VERY_HIGH_SPEED     3


#define PIN_STAT_ON         1
#define PIN_STAT_OFF        0

typedef struct
{
    void* Port_Num;
    uint32 Pin_Num;
    uint32 Mode;
    uint32 OutPut_Mode;
    uint32 OutPut_Speed;
    uint32 Input_Mode;
}GPIO_cfg_t;

typedef enum{
    pin0,
    pin1,
    pin2,
    pin3,
    pin4,
    pin5,
    pin6,
    pin7,
    pin8,
    pin9,
    pin10,
    pin11,
    pin12,
    pin13,
    pin14,
    pin15
}GPIO_Pin_t;

ErrorStatus_t GPIO_initPin(GPIO_cfg_t* PIN);
ErrorStatus_t GPIO_setPinValue(void* PORT,u8 pin,u8 value);
ErrorStatus_t GPIO_getPinValue(void* PORT,u8 pin,uint32* Pin_Stat);


#endif
