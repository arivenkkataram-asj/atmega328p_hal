#include "drivers/keypad_4x4.h"
#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"

#include <stdint.h>
uint8_t rows[4],cols[4];
uint8_t pullup_enable = 0;
uint8_t row_val=0,i,j,col_val =0;
uint8_t keypad_matrix[4][4] = { {1,2,3,4},
                                {5,6,7,8},
                                {9,10,11,12},
                                {13,14,15,16}
                                };
void keypad_4x4_init(uint8_t r0, uint8_t r1,
                     uint8_t r2, uint8_t r3,
                     uint8_t c0, uint8_t c1,
                     uint8_t c2, uint8_t c3, 
                     char pull_mode){
    
    rows[0] = r0; rows[1] = r1;
    rows[2] = r2; rows[3] = r3;
    cols[0] = c0; cols[1] = c1;
    cols[2] = c2; cols[3] = c3;
    for(uint8_t i=0;i<=3;i++){
        hal_gpio_init(rows[i],'O');
        hal_gpio_write(rows[i],1);
    }
    if(pull_mode == 'E'){
        pullup_enable = 1;
        for(uint8_t i=0;i<=3;i++){
            hal_gpio_init(cols[i],'I');
            hal_gpio_write(cols[i],1);
        }
    }else {
        for(uint8_t i=0;i<=3;i++){
            hal_gpio_init(cols[i],'I');
        }
    }
}
uint8_t keypad_4x4_read(){
    for(i=0;i<4;i++){
        row_val = i;
        for(uint8_t sel_row=0;sel_row<=3;sel_row++){
            if(sel_row != i){
                hal_gpio_write(rows[sel_row],1);
            }else{
                hal_gpio_write(rows[sel_row],0);
            }
        }

        delay_milli(1);
        for(j=0;j<4;j++){
            col_val = j;
            uint8_t x = hal_gpio_read(cols[j]);
            delay_milli(1);
            if(x == 0){
                return keypad_matrix[i][j];
            }else {
                continue;
            }
        }
        hal_gpio_write(rows[i],1);
    }
    return 0;
}