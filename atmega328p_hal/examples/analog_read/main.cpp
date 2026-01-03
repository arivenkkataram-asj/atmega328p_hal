#include <Arduino.h>
#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "hal/hal_adc.h"
uint16_t a0;
void setup() {
Serial.begin(9600);

while (1)
{
    a0 = hal_adc_read(0);
    Serial.println(a0);
    delay_milli(1000);
}

        
}
void loop() {
}