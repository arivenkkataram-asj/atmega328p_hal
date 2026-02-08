#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "hal/hal_timer.h"
#include "hal/hal_interrupt.h"
#include "hal/hal_uart.h"
#include "hal/hal_i2c.h"

int main(void){
  hal_systick_init();
  hal_enable_interrupt();
  hal_gpio_init(13,'O');
  hal_uart_init(9600);
  hal_i2c_init(100000);

  uint32_t LED_timer = 0;
  uint8_t LED_state = 0;
  while(1){
    if(hal_timeout_expired(LED_timer,1000)){ //blink LED every 1000ms and data transmit
      LED_timer = hal_millis();
      LED_state ^= 1;
      hal_gpio_write(13,LED_state);
      char start_ack = hal_i2c_start((0x12<<1)|0);
      if(start_ack == 1){
        hal_Serial_println((char *)"ACK Success");
      }else if(start_ack == 2){
        hal_Serial_println((char *)"NACK received");
      }else {
        hal_Serial_println((char *)"Error");
      }
      char transmit_ack = hal_i2c_write(0xAA);
      if(transmit_ack == 1){
        hal_Serial_println((char *)"Data transmitted and ack success.");
      }else if(transmit_ack == 2){
        hal_Serial_println((char *)"Data transmitted and NACK");
      }else {
        hal_Serial_println((char *)"Error");
      }
      hal_i2c_stop();
    }




  }
}
