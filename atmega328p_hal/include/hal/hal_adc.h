#ifndef HAL_ADC_H
#define HAL_ADC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint16_t hal_adc_read(uint8_t channel);


#ifdef __cplusplus
}
#endif

#endif