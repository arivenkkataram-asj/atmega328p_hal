# AVR HAL Timer (SysTick-like Millisecond Timer)

This module implements a **1 ms system tick timer** on **AVR ATmega328P** using **Timer0 in CTC mode**, designed as part of a **custom Hardware Abstraction Layer (HAL)**.

The implementation avoids Arduino core dependencies and directly programs hardware registers, making it suitable for **bare-metal embedded development** and **educational purposes**.

---

## Features

- 1 ms periodic interrupt using **Timer0 Compare Match A**
- 32-bit millisecond tick counter
- Atomic tick read (ISR-safe)
- Blocking delay (`hal_delay_ms`)
- Non-blocking timeout check (`hal_timeout_expired`)
- Fully register-level implementation
- Designed for **16 MHz system clock**

---

## Hardware & Configuration

### Target MCU
- ATmega328P (Arduino Uno compatible)

### Clock Configuration

| Parameter        | Value |
|------------------|-------|
| System Clock     | 16 MHz |
| Prescaler        | 256 |
| Timer Tick Rate  | 62,500 Hz |
| OCR0A Value      | 62 |
| Interrupt Period | ~1.004 ms (measured using logic analyzer) |

---

## Timer Mode Selection

Timer0 is configured in **CTC (Clear Timer on Compare Match)** mode.

### Waveform Generation Mode (WGM)

| WGM02 | WGM01 | WGM00 | Mode |
|-------|-------|-------|------|
|   0   |   1   |   0   |  CTC |

---

## Register Configuration

| Register |  Value | Purpose |
|----------|--------|---------|
| TCCR0A   | `0x02` | CTC mode |
| TCCR0B   | `0x04` | Prescaler = 256 |
| TCNT0    | `0x00` | Counter reset |
| OCR0A    | `62`   | Compare match value |
| TIMSK0   | `0x02` | Enable Compare Match A interrupt |

---

## File Structure

hal/
├── hal_timer.c
├── hal_timer.h
├── hal_interrupt.h
├── hal_gpio.h


---

## Core API

### `void hal_systick_init(void)`

Initializes Timer0 to generate a **1 ms system tick interrupt**.

Call this once during system initialization.

```c
hal_systick_init();
hal_enable_interrupt();
```

### uint32_t hal_millis(void)

- Returns the number of milliseconds elapsed since system start.
- Uses a 32-bit counter
- ISR-safe atomic read

```c
uint32_t time = hal_millis();
```

### void hal_delay_ms(uint32_t ms)

Blocking delay based on system ticks.

```c
hal_delay_ms(1000); // Delay 1 second
```
⚠️ This function blocks execution. Avoid using it in time-critical or low-power code paths.

### uint8_t hal_timeout_expired(uint32_t start, uint32_t duration)

Non-blocking timeout checker.
```c
uint32_t t0 = hal_millis();

if (hal_timeout_expired(t0, 500)) {
    // 500 ms elapsed
}
```
Returns:
1 → Timeout expired
0 → Still running

## Interrupt Service Routine
```c
ISR(TIMER0_COMPA_vect) {
    counter++;
}
```
- Executes every ~1 ms
- Increments a 32-bit global tick counter
- Minimal ISR workload (best practice)

## Atomic Read Strategy
Because AVR is an 8-bit architecture, reading a 32-bit variable must be protected.
```c
uint32_t hal_timer_get_ticks() {
    hal_disable_interrupt();
    uint32_t counters = counter;
    hal_enable_interrupt();
    return counters;
}
```
✔ Prevents corrupted reads
✔ ISR-safe design
✔ Demonstrates embedded best practices

## Verification

Timing verified using logic analyzer

Measured interrupt period: 1.004 ms

Error well within acceptable tolerance for software timing

