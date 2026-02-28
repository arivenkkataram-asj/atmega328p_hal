# ATMEGA328P HAL UART
## Overview
1. This module implements UART (USART0)dirver for ATmega328P.
2. This Operates in Asynchronous Normal Mode.
3. Direct register-level implementation (no avr-libc abstraction).

## Harware Details 
1. ATmega328P using external crystal - 16MHz.
2. USART0 of ATmega328P

### Register Used
|Register | Address | Purpose |
|:---------:|:---------:|:---------:|
|UCSR0A | 0xC0 | Status flags (RXC0, TXC0, UDRE0, U2X0) |
|UCSR0B | 0xC1 | RX/TX enable, Interrupt enable |
|UCSR0C | 0xC2 | Frame format |
|UBRR0 | 0xC4 | Baud rate register (12-bit) |
|UDR0 | 0xC6 | Data Register |

## Baud Rate Calculation

Formula (Normal Mode, U2X0 = 0) 
```
UBRR = (FCPU / (16 x Baud )) - 1
```
Formula (Asynchronous double speed mode)
```c
UBRR = (16000000/(8 x Baud))-1
```

This makes to setup the baud rate to the UBRR.

## Frame Formate Configuration

```c
*uart_UCSR0C = 0x06;
```

- Asynchronous mode.
- No parity
- 1 stop bit
- 8 data bits (8N1 format)

## API Description Section
### Functions
- `hal_uart_init(uint32_t baud)`
- `hal_uart_tx_byte(uint8_t data)`
- `hal_uart_rx_byte(void)`
- `hal_uart_rx_available(void)`
-  `hal_Serial_print()` and `hal_Serial_println()`

### ***hal_uart_init(uint32_t baud)***
1. This configures USART0
2. Sets Baud rate
3. Configures Frame formate (8bits, 1 stop bit, 1 start bit)
4. Enables Rx and Tx

Note: 
```This function should call before the RX/TX operations```

### ***hal_uart_tx_byte(uint8_t data)***
1. Waits for UDRE0 flag (bit5 of UCSR0A)
2. Writes to UDRO

### ***hal_uart_rx_byte(void)***
1. Blocking receive
2. Waits for RXC0 flag (bit7 of UCSR0A)
3. Returns received byte

### ***hal_uart_rx_available(void)***
1. Checks RXC0 flag
2. Non-blocking availability check

### ***hal_Serial_print()*** and ***hal_Serial_println()***
1. Sends null-terminated string
2. Line feed for newline

## Limitations
- Blocking Implementation
- No TX buffer
- No TX buffer
- No error handling (Framing error, Overrun, Parity error)
- Fixed 16MHz assumption
- Hardcoded register addresses

## Verification
- Tested with two microcontroller and USB-TTL converter
- Tested with the baud rates (9600, 115200)
- Verified via Serial terminal (Arduion Serial Monitor, mostly verified through the PlatformIO in VS Code).
- Loopback test validation.
