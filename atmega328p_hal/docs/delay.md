# Atmega328p Delay
Currently used the delay funtion as the cpu usage delay.
## delay_milli();
This function used to cpu comsumption for the 1milli second. 
#### Example:
```c
delay_milli(milli_sec);
```
## Limitation:
1. For the milli_sec starts from 1
2. Till 1000 the delay is approx 1.02sec. checking with the Logic Analyzer 24MHz 8Ch.
3. This will not give the timming accurate for using more than 1000(milli_sec).