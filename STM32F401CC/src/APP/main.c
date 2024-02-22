/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

//#include "GPIO.h"
#include "RCC.h"
int
main(int argc, char* argv[])
{
	//RCC_ControlClock(CLK_HSE_OSC,RCC_STAT_ON);
	//RCC_SelectSystemClock(SYS_CLK_HSE);
	//RCC_SelectSystemClock(SYS_CLK_HSI);
	//RCC_ControlClock(CLK_HSE_OSC,RCC_STAT_OFF);
	//RCC_SelectSystemClock(SYS_CLK_HSE);
	//RCC_ConfigurePLL(CLK_HSI,P_6,8,192);
	/*RCC_EnablePeripheral(AHB2,AHB2EN_OTGFS);
	RCC_DisablePeripheral(AHB2,AHB2EN_OTGFS);
	RCC_EnablePeripheral(AHB2,AHB1EN_DMA1);
	RCC_DisablePeripheral(AHB1,AHB2EN_OTGFS);
	*/
	RCC_SetAHB1Prescaler(HPRE_NDIV);
	RCC_SetAPB1Prescaler(PPRE1_2);
	RCC_SetAPB2Prescaler(PPRE2_4);
	RCC_SetAPB1Prescaler(PPRE2_8);
	/*
	RCC_EnablePeripheral (AHB1,EN_GPIOA);
    GPIO_cfg_t LED;
    LED.Port_Num=GPIOA;
    LED.Pin_Num=pin0;
    LED.Mode=MODE_OUTPUT;
    LED.OutPut_Mode=OPT_PP;
    LED.OutPut_Speed=MEDIUM_SPEED;
    GPIO_initPin(&LED);
  GPIO_setPinValue(GPIOA,pin0,PIN_STAT_ON);
  uint32 x=0;
  GPIO_getPinValue(GPIOA,pin0,&x);
  while (x<10)
	  x++;
	  */
	while (1)
	{

	}
	return 0;
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------




