#ifndef HAL_TIMER_H
#define HAL_TIMER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif
void hal_systick_init();
uint32_t hal_timer_get_ticks();
uint32_t hal_millis();
void hal_delay_ms(uint32_t ms);
uint8_t hal_timeout_expired(uint32_t start,uint32_t duration);


#ifdef __cplusplus
}
#endif

#endif