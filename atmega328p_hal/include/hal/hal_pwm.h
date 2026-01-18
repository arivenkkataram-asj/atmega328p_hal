#ifndef HAL_PWM_H
#define HAL_PWM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

void hal_pwm_init(uint16_t frequency);
void hal_pwm_channel_init(char channel);
void hal_pwm_set_duty(char channel,uint8_t duty);
void hal_pwm_start(uint8_t channel);
void hal_pwm_stop(uint8_t channel);

#ifdef __cplusplus
}
#endif

#endif