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
  hal_i2c_set_slave_address(0x12);
  uint32_t LED_timer = 0;
  uint8_t LED_state = 0;
  int receive_data;
  
  char i2c_listen_ack;
  while(1){
    if(hal_timeout_expired(LED_timer,500)){ //blink LED every 500ms
      LED_timer = hal_millis();
      LED_state ^= 1;
      hal_gpio_write(13,LED_state);
    }
    
    i2c_listen_ack = hal_i2c_slave_listen();
    if(i2c_listen_ack == 1){
      receive_data = hal_i2c_slave_read();
      if(receive_data == -2){
        hal_Serial_println("Stop Detected");
      }else if (receive_data == -1){
        hal_Serial_println("Error");
      }else if(receive_data >=0){
        hal_Serial_println("Received data");
      }
    }else if(i2c_listen_ack == 2){
      char write_ack = hal_i2c_slave_write(0x55);
    }else if(i2c_listen_ack == 3){
      hal_Serial_println("General_call");
    }
    

  }
}