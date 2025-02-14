// uart.c
#include "uart.h"
#include <string.h>

// Initialize UART
void UART_Init(uint32_t baudrate) {
    // Calculate BRR value
    uint32_t brr = (FUNCONF_SYSTEM_CORE_CLOCK + baudrate/2) / baudrate;

    // Enable GPIOD and UART clocks
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1;

    // Configure UART TX pin (PD5) - Push-Pull output
    GPIOD->CFGLR &= ~(0xf<<(4*5));
    GPIOD->CFGLR |= (GPIO_Speed_10MHz | GPIO_CNF_OUT_PP_AF)<<(4*5);

    // Configure UART RX pin (PD6) - Floating input
    GPIOD->CFGLR &= ~(0xf<<(4*6));
    GPIOD->CFGLR |= GPIO_CNF_IN_FLOATING<<(4*6);

    // Configure UART
    USART1->CTLR1 = USART_WordLength_8b | USART_Parity_No;
    USART1->CTLR2 = USART_StopBits_1;
    USART1->CTLR3 = 0;
    USART1->BRR = brr;

    // Enable UART TX and RX
    USART1->CTLR1 |= USART_Mode_Tx | USART_Mode_Rx | USART_CTLR1_UE;
}

// Enable UART receiver
void UART_EnableRx(void) {
    USART1->CTLR1 |= USART_Mode_Rx;
}

// Disable UART receiver
void UART_DisableRx(void) {
    USART1->CTLR1 &= ~USART_Mode_Rx;
}

// Enable UART transmitter
void UART_EnableTx(void) {
    USART1->CTLR1 |= USART_Mode_Tx;
}

// Disable UART transmitter
void UART_DisableTx(void) {
    USART1->CTLR1 &= ~USART_Mode_Tx;
}

// Send single character
void UART_SendChar(char ch) {
    while(!(USART1->STATR & USART_FLAG_TXE));
    USART1->DATAR = ch;
}

// Send string
void UART_SendString(const char* str) {
    while(*str) {
        UART_SendChar(*str++);
    }
}

// Check if data is available to read
bool UART_Available(void) {
    return (USART1->STATR & USART_FLAG_RXNE) != 0;
}

// Read single character
char UART_ReadChar(void) {
    while(!UART_Available());
    return USART1->DATAR;
}

// Read multiple bytes
uint8_t UART_ReadBytes(uint8_t* buffer, uint8_t length) {
    uint8_t count = 0;
    uint32_t timeout = 100000;

    while(count < length && timeout) {
        if(UART_Available()) {
            buffer[count++] = USART1->DATAR;
            timeout = 100000;
        }
        timeout--;
    }
    return count;
}

// Flush UART buffer
void UART_Flush(void) {
    while(!(USART1->STATR & USART_FLAG_TC));
}

// Get UART status
uint8_t UART_GetStatus(void) {
    return USART1->STATR;
}
