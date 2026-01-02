#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif 

void hal_gpio_init(uint8_t pin,char mode);
void hal_gpio_write(uint8_t pin,char mode);
void hal_gpio_pullup(uint8_t pin);
uint8_t hal_gpio_read(uint8_t pin);

#ifdef __cplusplus
}
#endif

#endif