// uart.h
#ifndef UART_H
#define UART_H

#include <stdbool.h>
#include <stdint.h>

#include "ch32v003fun.h"

// UART Status Flags
#define UART_TX_COMPLETE USART_FLAG_TC
#define UART_RX_COMPLETE USART_FLAG_RXNE
#define UART_OVERRUN_ERROR USART_FLAG_ORE
#define UART_FRAME_ERROR USART_FLAG_FE
#define UART_PARITY_ERROR USART_FLAG_PE

// Function prototypes
void UART_Init(uint32_t baudrate);
void UART_EnableRx(void);
void UART_DisableRx(void);
void UART_EnableTx(void);
void UART_DisableTx(void);
void UART_SendChar(char ch);
void UART_SendString(const char* str);
bool UART_Available(void);
char UART_ReadChar(void);
uint8_t UART_ReadBytes(uint8_t* buffer, uint8_t length);
void UART_Flush(void);
uint8_t UART_GetStatus(void);

#endif  // UART_H
