#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "hal/hal_timer.h"
#include "hal/hal_interrupt.h"
#include "hal/hal_pwm.h"
int main(void) { 
    hal_gpio_init(6,'O');
    hal_gpio_init(7,'O');
    hal_gpio_init(13,'O');
    hal_systick_init();
    hal_enable_interrupt();
    hal_pwm_init(100); //initializing the pwm with frequency 150Hz
    hal_pwm_channel_init(2); //initializing channel 2 pin no 10
    hal_pwm_set_duty(2,0); // setting initial duty 0%
    hal_pwm_channel_init(1); //initializing channel 1 pin no 9
    hal_pwm_set_duty(1,0);  // setting initial duty 0%
    uint32_t LED_timer = 0;
    uint8_t LED_out = 0;
    uint32_t Motor_timer = 0;
    uint8_t start_duty = 15;
    uint8_t end_duty = 70;
    uint8_t temp_duty = start_duty;
    uint8_t motor_dir = 0; // 0 for forward 1 for reverse
        while (1)
        {
            // continuous led blink
            if(hal_timeout_expired(LED_timer,500)){
                LED_timer = hal_millis();
                LED_out ^= 1;
                hal_gpio_write(13,LED_out);  
            }

            if(hal_timeout_expired(Motor_timer,1500)){
                Motor_timer = hal_millis();
                if(motor_dir == 0){
                    hal_gpio_write(6,1);
                    hal_gpio_write(7,0);
                }else{
                    hal_gpio_write(6,0);
                    hal_gpio_write(7,1);
                }
                if(temp_duty == end_duty){
                    temp_duty = start_duty;
                    motor_dir ^= 1;
                }
                hal_pwm_set_duty(2,temp_duty++); // forward channel B
                hal_pwm_start(2);
            
            }
            
        
        }
}
