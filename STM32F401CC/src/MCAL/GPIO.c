/*
 * GPIO.h
 *
 *  Created on: [Date]
 *      Author: [Author Name]
 */

#include "GPIO.h"
#include "STD_TYPES.h"
#include "Errors.h"

/************* GPIO Bit Masks to Configure 2 Bits ***************/
#define GPIO_TWO_BIT_MASK       0x00000003

/************* GPIO Bit Masks to Configure 4 Bits ***************/
#define GPIO_FOUR_BIT_MASK      0x0000000F

/************* GPIO Pin Offsets to Reach Desired Pin Bits ***************/
#define GPIO_PIN_OFFSET_2       0x00000002
#define GPIO_PIN_OFFSET_4       0x00000004

/************* BSRR Offset to Reach Reset Region***************/
#define BSRR_OFFSET             0x00000010

/************* GPIO Port Validation Macro ***************/
#define GPIO_VALIDATE_PORT(PTR)    (PTR == GPIOA || PTR == GPIOB || PTR == GPIOC || PTR == GPIOD || PTR == GPIOE || PTR == GPIOH)

typedef struct
{
    uint32 MODER;    /**< GPIO port mode register */
    uint32 OTYPER;   /**< GPIO port output type register */
    uint32 OSPEEDR;  /**< GPIO port output speed register */
    uint32 PUPDR;    /**< GPIO port pull-up/pull-down register */
    uint32 IDR;      /**< GPIO port input data register */
    uint32 ODR;      /**< GPIO port output data register */
    uint32 BSRR;     /**< GPIO port bit set/reset register */
    uint32 LCKR;     /**< GPIO port configuration lock register */
    uint32 AFRL;     /**< GPIO alternate function low register */
    uint32 AFRH;     /**< GPIO alternate function high register */
} GPIO_t;

ErrorStatus_t GPIO_initPin (GPIO_cfg_t* add_pin)
{
	ErrorStatus_t RetErrorStatus=NOK;
	/*Pointer to read Mode*/
	u8* ModeCheck_ptr=0;

	/*Validate Pointers*/
	if(add_pin==0 || add_pin->GPIO_Port_Num==0)
	{
		RetErrorStatus=NULL_PointerError;
	}
	else
	{
		/*ModeCheck_ptr holds Mode (output or input)*/
		/*ModeCheck_ptr++ holds Output_Mode (PP or OD)*/
			ModeCheck_ptr=(u8*)&add_pin->GPIO_Mode;
	}

	/*Validate struct fields GPIO_Port,GPIO_Pin,GPIO_Mode,GPIO_Output_Speed,GPIO_Pull,GPIO_AF*/
	if(!GPIO_VALIDATE_PORT((GPIO_t*)add_pin->GPIO_Port_Num))
	{
		RetErrorStatus=ParameterError;
	}
	else if (add_pin->GPIO_Pin_Num>15)
	{
		RetErrorStatus=ParameterError;
	}
	else if (*ModeCheck_ptr>GPIO_MODE_ANALOG)
	{
		RetErrorStatus=ParameterError;
	}
	/*validates Output_Mode hidden in Mode*/
	else if (*(++ModeCheck_ptr)>1)
	{
		RetErrorStatus=ParameterError;
	}
	else if (add_pin->GPIO_OutPut_Speed>GPIO_VHIGH_SPEED)
	{
		RetErrorStatus=ParameterError;
	}
	else if (add_pin->GPIO_Pull>GPIO_PULLDOWN)
	{
		RetErrorStatus=ParameterError;
	}
	else if (add_pin->GPIO_AF>GPIO_AF_EVENTOUT)
	{
		RetErrorStatus=ParameterError;
	}
	else
	{
		RetErrorStatus=OK;
		ModeCheck_ptr--;
		/***************** Configure Mode as Output or Input *****************/
		((GPIO_t*)(add_pin->GPIO_Port_Num))->MODER &=~ (GPIO_TWO_BIT_MASK<<GPIO_PIN_OFFSET_2*add_pin->GPIO_Pin_Num);
		((GPIO_t*)(add_pin->GPIO_Port_Num))->MODER |= (uint32)*ModeCheck_ptr<<(GPIO_PIN_OFFSET_2*add_pin->GPIO_Pin_Num);

		ModeCheck_ptr++;

		/***************** Configure Output Type as Push Pull or Open Drain *****************/
		//((GPIO_t*)(add_pin->GPIO_Port_Num))->OTYPER &=~ (1<<add_pin->GPIO_Pin_Num);
		((GPIO_t*)(add_pin->GPIO_Port_Num))->OTYPER |= (uint32)*ModeCheck_ptr<<add_pin->GPIO_Pin_Num;

		/***************** Configure Output Speed *****************/
		((GPIO_t*)(add_pin->GPIO_Port_Num))->OSPEEDR &= ~(GPIO_TWO_BIT_MASK<<GPIO_PIN_OFFSET_2*add_pin->GPIO_Pin_Num);
		((GPIO_t*)(add_pin->GPIO_Port_Num))->OSPEEDR |= add_pin->GPIO_OutPut_Speed<<(GPIO_PIN_OFFSET_2*add_pin->GPIO_Pin_Num);
		//((GPIO_t*)(PIN->GPIO_Port_Num))->PUPDR &=~ (1<<PIN->GPIO_Pin_Num);

		/***************** Configure pin as Pull Up or Pull Down *****************/
		((GPIO_t*)(add_pin->GPIO_Port_Num))->PUPDR |= add_pin->GPIO_Pull<<add_pin->GPIO_Pin_Num;

		/***************** Configure Alternate Function  *****************/
		if (add_pin->GPIO_Pin_Num<8)
		{
			/***************** AFRL used for Pins 0:7 *****************/
			((GPIO_t*)(add_pin->GPIO_Port_Num))->AFRL &=~ (GPIO_FOUR_BIT_MASK<<GPIO_PIN_OFFSET_4*add_pin->GPIO_Pin_Num);
			((GPIO_t*)(add_pin->GPIO_Port_Num))->AFRL |= add_pin->GPIO_AF<<(GPIO_PIN_OFFSET_4*add_pin->GPIO_Pin_Num);
		}

		else
		{
			/***************** AFRL used for Pins 8:15 *****************/
			((GPIO_t*)(add_pin->GPIO_Port_Num))->AFRH &=~ (GPIO_FOUR_BIT_MASK<<GPIO_PIN_OFFSET_4*add_pin->GPIO_Pin_Num);
			((GPIO_t*)(add_pin->GPIO_Port_Num))->AFRH |= add_pin->GPIO_AF<<(GPIO_PIN_OFFSET_4*add_pin->GPIO_Pin_Num);
		}
	}
	return RetErrorStatus;
}

ErrorStatus_t GPIO_setPinValue(void* GPIOx,u8 GPIO_pin,u8 GPIO_STATE)
{
	ErrorStatus_t RetErrorStatus = NOK;
	/***************** Validate Parameters  *****************/
	if (GPIOx==0)
	{
		RetErrorStatus=NULL_PointerError;
	}
	else if(!GPIO_VALIDATE_PORT((GPIOx)))
	{
		RetErrorStatus=ParameterError;
	}
	else if (GPIO_pin>15)
	{
		RetErrorStatus=ParameterError;
	}
	else if (GPIO_STATE != GPIO_STATE_HIGH && GPIO_STATE != GPIO_STATE_LOW)
	{
		RetErrorStatus=ParameterError;
	}
	else
	{
		RetErrorStatus=OK;
		if (GPIO_STATE==GPIO_STATE_LOW)
		{
			((GPIO_t*)GPIOx)->BSRR &= ~( (1<<(GPIO_pin+BSRR_OFFSET)));
		}
		else if (GPIO_STATE==GPIO_STATE_HIGH)
		{
			((GPIO_t*)GPIOx)->BSRR |= (1<<GPIO_pin);
		}
	}
	return RetErrorStatus;

}

ErrorStatus_t GPIO_getPinValue(void* GPIOx,u8 GPIO_pin,u8* Pin_Stat)
{
	ErrorStatus_t RetErrorStatus = NOK;
	if (Pin_Stat==0)
	{
		RetErrorStatus=NULL_PointerError;
	}
	else if(!GPIO_VALIDATE_PORT((GPIOx)))
	{
		RetErrorStatus=ParameterError;
	}
	else if (GPIO_pin>15)
	{
		RetErrorStatus=ParameterError;
	}
	else
	{
		RetErrorStatus = OK;
		*Pin_Stat = ((GPIO_t*)GPIOx)->IDR & (1<<GPIO_pin);
	}

	return RetErrorStatus;
}
