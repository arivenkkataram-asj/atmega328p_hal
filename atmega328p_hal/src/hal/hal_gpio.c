#include <stdint.h>
#include "hal/hal_gpio.h"
//Port-B 
uint8_t port_b; //initilizing the output & input pins of Port-B
uint8_t port_b_output; //output values of the port-B
uint8_t port_b_input; //input values of the port-B

//Port-C  
uint8_t port_c; //initilizing the output pins of Port-c
uint8_t port_c_output; //output values of the port-C
uint8_t port_c_input; //input values of the Port-C

//Port-D -->Ouput
uint8_t port_d; // initilizing the output pins of Port-D
uint8_t port_d_output; //output values of the port-C
uint8_t port_d_input; //input values of the port-D

//initilizing the port_b Register for the Output 
void init_port_b(uint8_t port_b_pins){
    volatile uint8_t *dirb = (volatile uint8_t *)0x24;
    *dirb = port_b_pins;
}


//initilizing the port_c Register; for the Output
void init_port_c(uint8_t port_c_pins){
    volatile uint8_t *dirc = (volatile uint8_t *)0x27;
    *dirc = port_c_pins;
}

//initilizing the port-d Register; for the Output
void init_port_d(uint8_t port_d_pins){
    volatile uint8_t *dird = (volatile uint8_t *)0x2A;
    *dird = port_d_pins;
}

//geting the input from the main.cpp
void hal_gpio_init(uint8_t pin,char mode){
    if(pin >= 8 && pin <= 13 ){ // Port B 
        if(mode == 1 || mode == 'O'){ //Checking Mode is output
            port_b |=  (1<<(pin - 8));
            init_port_b(port_b);
        }
        else if(mode == 0 || mode == 'I'){
            port_b &= ~(0<<(pin - 8));
            init_port_b(port_b);
        }
    }
    else if(pin >= 14 && pin <= 19){ //Port C
        if(mode == 1 || mode == 'O'){ //Checking Mode is Output
            port_c |= (1<<(pin - 14));
            init_port_c(port_c);
        }
        else if(mode == 0 || mode == 'I'){
            port_c &= ~(0<<(pin - 14));
            init_port_c(port_c);
        }
    }
    else if(pin >= 2 && pin <= 7){ //Port D
        if(mode == 1 || mode == 'O') { //Checking Mode is Output
            port_d |= (1<<(pin));
            init_port_d(port_d);
        }
        else if(mode == 0 || mode == 'I'){
            port_d &= ~(0<<(pin));
            init_port_d(port_d);
        }
    }
}


//writing the gpio pin as high or low
void hal_gpio_write(uint8_t pin,char mode){
    if(pin >= 8 && pin <=13){ //Port - B
        volatile uint8_t *out_b =(volatile uint8_t *) 0x25;
        if(mode == 1 ){ //check output is high
            port_b_output |=  (1<<(pin - 8));
            *out_b = port_b_output;
        }
        else if(mode == 0){ //Output is LOW
            port_b_output &=  ~(1<<(pin - 8));
            *out_b = port_b_output;
        }
    }
    else if(pin >= 14 && pin <= 19){ // Port - C
        volatile uint8_t *out_c = (volatile uint8_t *)0x28;
        if(mode == 1){ // Ouput High
            port_c_output |= (1<<(pin - 14));
            *out_c = port_c_output; 
        } 
        else if(mode == 0){ // Output is Low
            port_c_output &= ~(1<<(pin - 14));
            *out_c = port_c_output;     
        }
    }
    else if(pin >= 2 && pin <= 7){ // Port - D
        volatile uint8_t *out_d = (volatile uint8_t *)0x2B;
        if(mode == 1){ // Output is High
            port_d_output |= (1<<pin);
            *out_d = port_d_output;
        }
        else if(mode == 0){ //Output is Low
            port_d_output &= ~(1<<pin);
            *out_d = port_d_output;
        }
    }
}

void hal_gpio_pullup(uint8_t pin){    
        hal_gpio_write(pin, 1);    
}

uint8_t hal_gpio_read(uint8_t pin){
    if(pin >= 8 && pin <=13){ //Port - B
        volatile uint8_t *in_b = (volatile uint8_t *)0x23;
        uint8_t port_b_input = (*in_b & (1<<(pin-8)))==(1<<(pin-8));  
        return port_b_input;
    }
    else if(pin >= 14 && pin <=19){ //port C
        volatile uint8_t *in_c = (volatile uint8_t *)0x26;
        return (*in_c & (1<<(pin - 14))) == (1<<(pin-14));
    }
    else if(pin >= 2 && pin <= 7){ //port D
        volatile uint8_t *in_d = (volatile uint8_t *)0x29;
        return (*in_d & (1<<(pin))) == (1<<(pin));
    }else {
        return 0;
    }
}