#ifndef HAL_UART_H
#define HAL_UART_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

void hal_uart_init(uint32_t baud);
void hal_uart_tx_byte(uint8_t tx_data);
uint8_t hal_uart_rx_byte(void);
uint8_t hal_uart_rx_available(void);
void hal_Serial_println(char sentence[]);
void hal_Serial_print(char sentence[]);

#ifdef __cplusplus
}
#endif

#endif