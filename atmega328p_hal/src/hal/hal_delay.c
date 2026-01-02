#include "hal/hal_delay.h"
#include<stdint.h>
/*
delay milli(1) == 1ms 
using of delay-milli(1000) = 1.02s 
*/
volatile void delay_milli(int milli_sec){ 
    volatile long i;
    for(int j=0;j<milli_sec;j++){
        for(i=0;i<452;i++);
    }
    for(i=0;i<0;i++);
}