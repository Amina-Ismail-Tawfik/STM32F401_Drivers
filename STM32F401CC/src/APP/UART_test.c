#include "RCC.h"
#include "GPIO.h"
#include "NVIC.h"
#include "UART.h"
#include "sched.h"
void TxCB()
{

}
int main()
{

	RCC_EnablePeripheral(AHB1,AHB1EN_GPIOA);
	RCC_EnablePeripheral(APB2,APB2EN_USART1);
	GPIO_cfg_t Tx_pin;
	Tx_pin.GPIO_Port_Num=GPIOA;
	Tx_pin.GPIO_Pin_Num=GPIO_pin0;
	Tx_pin.GPIO_Mode=GPIO_MODE_AF;
	Tx_pin.GPIO_AF=GPIO_AF_USART1_2;
	Tx_pin.GPIO_OutPut_Speed=GPIO_HIGH_SPEED;
	Tx_pin.GPIO_Pull=GPIO_NOPULL;
	GPIO_cfg_t Rx_pin;
	Rx_pin.GPIO_Port_Num=GPIOA;
	Rx_pin.GPIO_Pin_Num=GPIO_pin0;
	Rx_pin.GPIO_Mode=GPIO_MODE_AF;
	Rx_pin.GPIO_AF=GPIO_AF_USART1_2;
	Rx_pin.GPIO_OutPut_Speed=GPIO_HIGH_SPEED;
	Rx_pin.GPIO_Pull=GPIO_NOPULL;
	GPIO_initPin(&Tx_pin);
	GPIO_initPin(&Rx_pin);
	uint8_t myData[10]={1,2,3,4,5,6,7,8,9,10};
	NVIC_EnableIRQ(IRQ_USART1);
	UART_enableInterrupts(UART1);
	UART_TxBufferAsync(UART1,myData,10,TxCB);

	/*sched_init();
	sched_RegisterRunnable(&UART_TxRunnable);
	sched_start();*/
	return 0;
}
