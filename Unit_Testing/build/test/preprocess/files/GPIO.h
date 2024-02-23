#include "../STM32F401CC/include/Errors.h"
#include "../STM32F401CC/include/STD_TYPES.h"






typedef struct

{

    void* GPIO_Port_Num;

    u8 GPIO_Pin_Num;

    uint16 GPIO_Mode;

    u8 GPIO_OutPut_Speed;

    u8 GPIO_Pull;

    u8 GPIO_AF;

} GPIO_cfg_t;





typedef enum{

    GPIO_pin0,

    GPIO_pin1,

    GPIO_pin2,

    GPIO_pin3,

    GPIO_pin4,

    GPIO_pin5,

    GPIO_pin6,

    GPIO_pin7,

    GPIO_pin8,

    GPIO_pin9,

    GPIO_pin10,

    GPIO_pin11,

    GPIO_pin12,

    GPIO_pin13,

    GPIO_pin14,

    GPIO_pin15

} GPIO_Pin_t;

ErrorStatus_t GPIO_initPin (GPIO_cfg_t* add_pin);

ErrorStatus_t GPIO_setPinValue(void* GPIOx, u8 GPIO_pin, u8 GPIO_STATE);

ErrorStatus_t GPIO_getPinValue(void* GPIOx, u8 GPIO_pin, u8* Pin_Stat);
