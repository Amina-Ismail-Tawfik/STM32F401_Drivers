#include <LCD_app.h>

runnable_t LCD_Runnable={
		.name="LCD",
		.priority=1,
		.periodicity=50,
		.CB=myLCD_APP
};


void myLCD_APP()
{
	static uint32_t counter=0;
	if (counter==0)
	{
	 LCD_initAsyn();
	 counter++;
	}
	else if (counter==1)
	{
	LCD_writeStringAsyn("Amina",50);
	counter++;
	}
	else if (counter==2)
	{
	LCD_setCursorPosAsyn(1,4);
	counter++;
	}
	else if (counter==3)
	{
	LCD_writeStringAsyn("Suhila",50);
	counter=1000;
	}
}
