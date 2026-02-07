#include "hal/hal_uart.h"

void hal_uart_init(uint32_t baud){
    /*
    16000000 is 16MHz crystal . the Formula from the datasheet
    here it set to the Asynchronous normal mode (U2Xn = 0)
    UBRRn = (f_OSC/16BAUD)-1
    eg: baud = 9600;
    UBRR_data = 103;
    UBRR0 allows 12 bit so 0 to 4096
    */
    uint16_t UBRR_data = (16000000/(8*baud))-1;
    //disable rx and tx;
    volatile uint8_t *uart_UCSR0B = (volatile uint8_t *)0xC1;
    *uart_UCSR0B = 0;
    //setting the baud rate.
    volatile uint16_t *uart_UBRR0 = (volatile uint16_t *)0xC4;
    *uart_UBRR0 = UBRR_data;
    //setting frame rate
    volatile uint8_t *uart_UCSR0C = (volatile uint8_t *)0xC2;
    *uart_UCSR0C = 0x06;
    volatile uint8_t *uart_UCSR0A = (volatile uint8_t *)0xC0;
    *uart_UCSR0A = 0x02;
    /*
    enable rx and tx & enabling the interrupt 
    bit7 - enable RX Complete interrupt 
    bit6 - enable TX complete interrupt
    */
    *uart_UCSR0B = (0x18); 
}


void hal_uart_tx_byte(uint8_t data){
    volatile uint8_t *uart_UCSR0A = (volatile uint8_t *)0xC0;
    while(!(*uart_UCSR0A & 0x20));
    volatile uint8_t *uart_UDR0 = (volatile uint8_t *)0xC6;
    *uart_UDR0 = data;
}


uint8_t hal_uart_rx_byte(void){
    volatile uint8_t *uart_UCSR0A = (volatile uint8_t *)0xC0;
    while(!(*uart_UCSR0A & 0x80));
    volatile uint8_t *uart_UDR0 = (volatile uint8_t *)0xC6;
    return (*uart_UDR0 );
}


uint8_t hal_uart_rx_available(void){
    volatile uint8_t *uart_UCSR0A = (volatile uint8_t *)0xC0;
    return (*uart_UCSR0A & 0x80) ? 1 : 0;
}

void hal_Serial_print(char sentence[]){
  char i=0;
  while(sentence[i] != '\0'){
    hal_uart_tx_byte(sentence[i]);
    i++;
  }
}

void hal_Serial_println(char sentence[]){
  hal_Serial_print(sentence);
  hal_uart_tx_byte(0x0A);
}
