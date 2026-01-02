#include "hal/hal_gpio.h"
//uploading this there is noise build up in the digital pin no 13
//Port no 13 will glow dim according to the blink of the any port b pins as 0-4
//need to check on this code...
void delay(){
    volatile long i;
    for(i=0;i<100000;i++);
}
int main(void){
    hal_gpio_init(11,'O');

    while(1){
        hal_gpio_write(11,1);
        delay();
        hal_gpio_write(11,0);
        delay();
    
    }
}