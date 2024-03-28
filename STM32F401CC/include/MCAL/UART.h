#ifndef UART_H
#define UART_H
#include <stdint.h>
#include "Errors.h"
#include <sched.h>
#define UART1_BASE_ADDRESS 					0x40011000
#define UART2_BASE_ADDRESS					0x40004400
#define UART6_BASE_ADDRESS					0x40011400

#define UART1     (void *)UART1_BASE_ADDRESS
#define UART2     (void *)UART2_BASE_ADDRESS
#define UART3	  (void *)UART6_BASE_ADDRESS

typedef void (*Txcb_t)(void);
typedef void (*Rxcb_t)(void);

void UART_enableInterrupts(void* UARTx);
ErrorStatus_t UART_TxBufferAsync(void* UARTx,uint8_t* buffer,uint16_t length,Txcb_t cb);
ErrorStatus_t UART_TxDone();
ErrorStatus_t UART_RxBufferAsync(void* UARTx,uint8_t* buffer,uint16_t length,Rxcb_t cb);


#endif
