# ATMega328P HAL ADC

## Overview
This `hal_adc.h` used for the returning for the analog read of the Sensors. By using of the single function call. 

## Supported Features
- Channel Range A0 to A7
- Resolution is 0 to 1023
- Reference Voltage is 1.1V (internally enabled)

## ADC Reference Voltage
- ADC Reference Voltage is set as default as the 1.1v. Since it is internally enabled.
- For the internally enabled voltage reference can detect only the voltage range of 0 to 1.1V 

## ADC Conversion Model
1. In this `hal_adc.h` uses the Blocking Conversion Flow.
2. Start --> wait --> read the result.
3. This is design flow of the `hal_adc.h`.

## Channel Selection
1. That channel select through the 0 to 7 valid number.
2. If invalid number it will return only zero(0).

## Result Format & Resolution
1. ADC resolution (10 - bit).
2. Value range is 0 to 1023.
3. By default it is Right adjusted.

## Public API Description
### List of Pulic Funtion
#### 1. hal_adc_read();
This funtion is reads the adc_Value and return in formate of 0 to 1023.
##### Example:
```c
hal_adc_read(channel_no);
```
#### Channel No
- A0 - 1
- A1 - 2
- A3 - 3
- A4 - 4
- A5 - 5
- A6 - 6
- A7 - 7

## Limitation
1. This `hal_adc.h` sets the 1.1V as the default.
2. Uses blocking flow for analog read.

## Testing
1. Anolog value is tested through the potentiometer through the Arduino UNO developement board.