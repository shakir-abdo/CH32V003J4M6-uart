#include "uart.h"

int main() {
    SystemInit();

    // Initialize UART with 115200 baud rate
    UART_Init(115200);

    // Send welcome message
    UART_SendString("UART Test\r\n");

    while(1) {
        if(UART_Available()) {
            char ch = UART_ReadChar();
            UART_SendChar(ch);
        }
    }
}
