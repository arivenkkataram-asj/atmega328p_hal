#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "hal/hal_timer.h"
#include "hal/hal_interrupt.h"
#include "hal/hal_uart.h"


int main(void){
  hal_systick_init();
  hal_enable_interrupt();
  hal_gpio_init(13,'O');
  hal_uart_init(9600);
  uint32_t LED_timer = 0;
  uint8_t LED_state = 0;
  uint32_t UART_timer = 100;
  uint8_t data = 65;
  char sentence[] = "Caps Alphabets: ";
  while(1){
    if(hal_timeout_expired(LED_timer,500)){ //blink LED every 500ms
      LED_timer = hal_millis();
      LED_state ^= 1;
      hal_gpio_write(13,LED_state);
    }
    if(data>90){
      data = 65;
      hal_Serial_println((char *)" Ended going to next line.");      
    }
    
    if(hal_timeout_expired(UART_timer,100)){ //sending every 1000ms
      UART_timer = hal_millis();
      if(data==65){
        hal_Serial_print(sentence);
      }
      hal_uart_tx_byte(data);  //printing from 65 to 89 ASCII value...
      data ++;
    }

  }
}