#include <LCD.h>
#include <GPIO.h>

const LCD_cfg_t LCD_pins [_LCD_ARR_SIZE]= {
	 [_EN]={.LCD_Port=GPIOB,
			.LCD_Pin=GPIO_pin0},
	 [_RS]={.LCD_Port=GPIOB,
				.LCD_Pin=GPIO_pin1},
	 [_RW]={.LCD_Port=GPIOB,
				.LCD_Pin=GPIO_pin2},
	[_D0]={.LCD_Port=GPIOB,
				.LCD_Pin=GPIO_pin3},
	[_D1]={.LCD_Port=GPIOB,
				.LCD_Pin=GPIO_pin4},
	[_D2]={.LCD_Port=GPIOB,
				.LCD_Pin=GPIO_pin5},
	[_D3]={.LCD_Port=GPIOB,
				.LCD_Pin=GPIO_pin6},
	[_D4]={.LCD_Port=GPIOB,
				.LCD_Pin=GPIO_pin7},
	[_D5]={.LCD_Port=GPIOB,
				.LCD_Pin=GPIO_pin8},
	[_D6]={.LCD_Port=GPIOB,
				.LCD_Pin=GPIO_pin9},
	[_D7]={.LCD_Port=GPIOB,
				.LCD_Pin=GPIO_pin10}
		};
