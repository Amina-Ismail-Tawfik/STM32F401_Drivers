/*
 * UART.c
 *
 *  Created on: Mar 25, 2024
 *      Author: Amina Ismail
 */
#include <UART.h>


#define READY 	0
#define BUSY	1
#define DATA_MASK   0x00000100
#define TXE_MASK 	0x00000080
#define RXNE_MASK	0x00000020
#define UE_MASK		0x00002000
#define M_MASK		0x00001000
#define TE_MASK     0x00000008
#define STOP_MASK   0x00003000

void UART_TxTask();
void UART_RxTask();


typedef struct{
	uint32_t SR;
	uint32_t DR;
	uint32_t BRR;
	uint32_t CR1;
	uint32_t CR2;
	uint32_t CR3;
	uint32_t GTPR;
}UART;

typedef struct{
	uint8_t *data;
	uint32_t pos;
	uint32_t size;
}buffer_t;
struct{
	buffer_t buffer;
	uint8_t state;
	UART* UARTx;
	Txcb_t cb;
}Tx_req;
struct{
	buffer_t buffer;
	uint8_t state;
	UART* UARTx;
	Rxcb_t cb;
}Rx_req;

void UART_sendByte();

ErrorStatus_t UART_TxBufferAsync(void* UARTx,uint8_t* buffer,uint16_t length,Txcb_t cb)
{
	ErrorStatus_t RetErrorStatus=NOK;
	uint32_t loc_register;
	if(Tx_req.state==READY)
	{
		Tx_req.state=BUSY;
		Tx_req.buffer.data=buffer;
		Tx_req.buffer.size=length;
		Tx_req.buffer.pos=0;
		Tx_req.UARTx=(UART*)UARTx;
		Tx_req.cb=cb;
		loc_register=Tx_req.UARTx->CR1;
		loc_register|=UE_MASK;
		loc_register&=~M_MASK;
		Tx_req.UARTx->CR1 = loc_register;

		loc_register=Tx_req.UARTx->CR2;
		loc_register&=~STOP_MASK;
		Tx_req.UARTx->CR2=loc_register;

		loc_register=Tx_req.UARTx->CR1;
		loc_register|=TE_MASK;
		Tx_req.UARTx->CR1 = loc_register;

		loc_register=Tx_req.UARTx->DR;
		loc_register|=Tx_req.buffer.data[Tx_req.buffer.pos];
		Tx_req.UARTx->DR =loc_register;
		Tx_req.buffer.pos++;
	}
	else
		RetErrorStatus=ConfigurationError;
	return RetErrorStatus;
}

void UART_sendByte()
{
	if (Tx_req.buffer.pos<Tx_req.buffer.size)
	{

		if (Tx_req.UARTx->SR&TXE_MASK)
		{
			uint32_t loc_register;
			loc_register=Tx_req.UARTx->DR;
			loc_register|=Tx_req.buffer.data[Tx_req.buffer.pos];
			Tx_req.UARTx->DR =loc_register;
			Tx_req.buffer.pos++;
		}
	}
	else
	{
		if(Tx_req.cb)
			Tx_req.cb();
		Tx_req.state=READY;
	}
}

ErrorStatus_t UART_RxBufferAsync(void* UARTx,uint8_t* buffer,uint16_t length,Rxcb_t cb)
{
	ErrorStatus_t RetErrorStatus=NOK;
	if(Rx_req.state==READY)
	{
		Rx_req.state=BUSY;
		Rx_req.buffer.data=buffer;
		Rx_req.buffer.size=length;
		Rx_req.buffer.pos=0;
		Rx_req.UARTx=(UART*)UARTx;
		Rx_req.cb=cb;
	}
	else
		RetErrorStatus=ConfigurationError;
	return RetErrorStatus;
}

void UART_receiveByte()
{
	if (Rx_req.buffer.pos<Rx_req.buffer.size)
	{
		if(Rx_req.UARTx->SR&RXNE_MASK)
		{
			Rx_req.buffer.data[Tx_req.buffer.pos]=(uint8_t)Rx_req.UARTx->DR;
			Rx_req.buffer.pos++;
		}
	}
	else
	{
		if(Rx_req.cb)
			Rx_req.cb();
		Rx_req.state=READY;
	}

}

void UART_TxTask()
{
	switch(Tx_req.state)
	{
	case BUSY:
		UART_sendByte(Tx_req.buffer.data[Tx_req.buffer.pos]);
		break;

	case READY:
		/*do nothing*/
		break;

	default:
		break;
	}
}

void UART_RxTask()
{
	switch(Rx_req.state)
	{
	case BUSY:
		UART_receiveByte();
		break;
	case READY:
		/*do nothing*/
		break;
	default:
		break;
	}
}

void UART_handler()
{
	if (Tx_req.UARTx->SR&TXE_MASK)
	{
		UART_sendByte(Tx_req.buffer.data[Tx_req.buffer.pos]);
	}
	if (Rx_req.UARTx->SR&RXNE_MASK)
	{
		UART_receiveByte();
	}
}
void UART_enableInterrupts(void* UARTx)
{
	Tx_req.UARTx=(UART*)UARTx;
	Rx_req.UARTx=(UART*)UARTx;
	uint32_t loc_register;
	loc_register=Tx_req.UARTx->CR1;
	loc_register|=TXE_MASK;
	loc_register|=RXNE_MASK;
	Tx_req.UARTx->CR1=loc_register;
}
void USART1_IRQHandler()
{
	UART_handler();
}
void USART2_IRQHandler(void)
{
	UART_handler();
}
void USART6_IRQHandler(void)
{
	UART_handler();
}
