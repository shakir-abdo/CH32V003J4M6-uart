# CH32V003 UART Library

A simple and efficient UART library for CH32V003 microcontroller.

## Features

- Configurable baud rate
- TX/RX control
- Single character and string transmission
- Buffer management
- Error checking

## Installation

1. Copy the library to your PlatformIO project's `lib` directory
2. Include the header file in your project:

```c
   #include "uart.h"
```
## Pinout
USB-To-TTL RX -> Ch32v0003j4m6 [PD1/PD4/PD5/SWIO]

USB-To-TTL TX -> Ch32v0003j4m6 [PA1/PD6]

## Usage
```c
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

```

