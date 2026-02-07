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
  char sentence[] = "Ready to Receive";
  char receive_data;
  while(1){
    if(hal_timeout_expired(LED_timer,500)){ //blink LED every 500ms
      LED_timer = hal_millis();
      LED_state ^= 1;
      hal_gpio_write(13,LED_state);
    }
    
    receive_data = hal_uart_rx_byte();
    hal_uart_tx_byte(receive_data);
    

  }
}