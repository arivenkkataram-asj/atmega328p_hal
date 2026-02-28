# AVR HAL Interrupt (Enable and Disable global interrupt)

This module implements to **enable** and **disable** the Global Interrupt to safe guard the current processing of the values.
Prevents data corruption caused by concurrent access between main context and ISR.
--- 

## Features

- Interrupt enable
- Interrupt disable

---

## Hardware & Configuration
### Target MCU
- ATmega328p (Arduino UNO and Arduino NANO compatible)

## API
### `hal_enable_interrupt(void)`

Initializes the CPU to Accepts the Interrups.

Call this function can be calls many time whenever needed in the code.

```c
hal_enable_interrupt();
```

### `hal_disable_interrupt(void)`

This disables the interrupt to the CPU.
At this time any interrupts from external or internal interrupts are interrupt requests are ignored the Global Interrupt Flag (I-bit) in SREG is cleared, Until the `hal_enable_interrupt()`.

```c
hal_disable_interrupt();
```

## Use Case
Typically used while accessing shared variables between main context and ISR.
- Protect multi-byte variable access (16-bit/32-bit)

- Protect shared resources between main() and ISR

- Prevent race conditions
## Verification
1. This is hardcoded hex values to the API
2. Interrupt is working good.
