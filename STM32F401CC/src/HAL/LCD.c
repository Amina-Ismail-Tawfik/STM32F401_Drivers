/*
 * LCD.c
 *
 *  Created on: Mar 20, 2024
 *      Author: adel
 */
#include <LCD.h>
#include <GPIO.h>
#define OFF 		1
#define INIT		0
#define OPERATION	2

#define POWER_ON		0
#define FUNCTIONAL_SET	0x38
#define DISPLAY_ON_OFF	0x0C
#define DISPLAY_CLEAR	0x01
#define	ENTRY_MODE		0x06
#define END				0x10

#define REQ_WRITE	1
#define REQ_SET_CURSOR	2
#define REQ_CLEAR_SCREEN	3
#define REQ_GET_STATE	4
#define REQ_INIT		5

#define BUSY	1
#define	READY 	0



struct{
	uint8_t type;
	uint8_t state;
	char* string;
	uint8_t len;
}user_request;





uint8_t EN_status;
uint8_t LCD_State;
uint8_t init_State;
uint8_t ReqType;
extern const LCD_cfg_t LCD_pins[_LCD_ARR_SIZE];

void LCD_task();
static void initSM();
static void statLCD_Write_Command(uint8_t command);
static ErrorStatus_t stat_writeString();

runnable_t LCD={
		.name="runnable2",
		.priority=2,
		.periodicity=2,
		.CB=LCD_task
};
ErrorStatus_t LCD_initAsyn()
{
	ErrorStatus_t RetErrorStatus=NOK;
	if (user_request.state==READY && init_State!=END)
		{
			user_request.state=BUSY;
			user_request.type=REQ_INIT;

		}
	return RetErrorStatus;
}
ErrorStatus_t LCD_writeStringAsyn(char*string,uint8_t length)
{
	ErrorStatus_t RetErrorStatus=NOK;
	if (user_request.state==READY)
	{
		user_request.state=BUSY;
		user_request.type=REQ_WRITE;
		user_request.string=string;
		user_request.len=length;
	}
	return RetErrorStatus;
}
static ErrorStatus_t stat_writeString()
{
	ErrorStatus_t RetErrorStatus;
	GPIO_setPinValue(LCD_pins[_RS].LCD_Port,LCD_pins[_RS].LCD_Pin,GPIO_STATE_HIGH);				/*	switch to instruction mode	*/
	GPIO_setPinValue(LCD_pins[_RW].LCD_Port,LCD_pins[_RW].LCD_Pin,GPIO_STATE_LOW);				/*	switch to write mode	*/
	static uint8_t charIDX;
	if (charIDX<user_request.len && user_request.string[charIDX]!= '\0')
	{
		for(uint8_t idx=_D0;(idx<=_D7);idx++)
		{
			GPIO_setPinValue(LCD_pins[idx].LCD_Port,LCD_pins[idx].LCD_Pin,(user_request.string[charIDX]>>(idx-_D0)) & 1);	/*	assign commands to data pins bit by bit	*/
		}
		GPIO_getPinValue(LCD_pins[_EN].LCD_Port,LCD_pins[_EN].LCD_Pin,&EN_status);
		EN_status=EN_status^1;
		GPIO_setPinValue(LCD_pins[_EN].LCD_Port,LCD_pins[_EN].LCD_Pin,EN_status);
		if (EN_status==0)
			charIDX++;
	}
	else
	{
		user_request.state=READY;
	}
	return RetErrorStatus;
}

static void statLCD_Write_Command(uint8_t command)
{
	GPIO_setPinValue(LCD_pins[_RS].LCD_Port,LCD_pins[_RS].LCD_Pin,GPIO_STATE_LOW);				/*	switch to instruction mode	*/
	GPIO_setPinValue(LCD_pins[_RW].LCD_Port,LCD_pins[_RW].LCD_Pin,GPIO_STATE_LOW);				/*	switch to write mode	*/

	for(uint8_t idx=_D0;idx<=_D7;idx++)
	{
		GPIO_setPinValue(LCD_pins[idx].LCD_Port,LCD_pins[idx].LCD_Pin,(command>>(idx-_D0) & 1));	/*	assign commands to data pins bit by bit	*/
	}
	GPIO_getPinValue(LCD_pins[_EN].LCD_Port,LCD_pins[_EN].LCD_Pin,&EN_status);
	EN_status=EN_status^1;
	GPIO_setPinValue(LCD_pins[_EN].LCD_Port,LCD_pins[_EN].LCD_Pin,EN_status);

}
//every 2ms
static void initSM()
{
	GPIO_cfg_t LCD_initPin;
	switch(init_State)
	{
	case POWER_ON:
		LCD_initPin.GPIO_OutPut_Speed=GPIO_HIGH_SPEED;
		LCD_initPin.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
		uint8_t idx=0;
		for (idx=0;idx<_LCD_ARR_SIZE;idx++)
		{
			LCD_initPin.GPIO_Port_Num=LCD_pins[idx].LCD_Port;
			LCD_initPin.GPIO_Pin_Num=LCD_pins[idx].LCD_Pin;
			GPIO_initPin(&LCD_initPin);
		}
		init_State=FUNCTIONAL_SET;
		break;
	case FUNCTIONAL_SET:
		statLCD_Write_Command(FUNCTIONAL_SET);
		if (EN_status==0)
			init_State=DISPLAY_ON_OFF;
		break;
	case DISPLAY_ON_OFF:
		statLCD_Write_Command(DISPLAY_ON_OFF);
		if (EN_status==0)
			init_State=DISPLAY_CLEAR;;
		break;
	case DISPLAY_CLEAR:
		statLCD_Write_Command(DISPLAY_CLEAR);
		if (EN_status==0)
			init_State=ENTRY_MODE;
		break;
	case ENTRY_MODE:
		statLCD_Write_Command(ENTRY_MODE);
		if (!EN_status==0)
		{
			init_State=END;
			user_request.state=READY;
		}
			break;
	case END:
		break;
	default:
		break;

	}
}

void LCD_task()
{
	switch (LCD_State)
	{
	case INIT:
		initSM();
		if (init_State==END)
			LCD_State=OPERATION;
		break;
	case OPERATION:
		if(user_request.state==BUSY)
		{
			switch(user_request.type)
			{
			case REQ_WRITE:
				stat_writeString();
				break;
			}
		}


		break;
	}
}



