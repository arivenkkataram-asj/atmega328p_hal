#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void seven_segment_init(uint8_t a,uint8_t b,
                        uint8_t c,uint8_t d,
                        uint8_t e,uint8_t f,
                        uint8_t g,char dp,
                        char type);
void seven_segment_display(uint8_t num,char dot);


#ifdef __cplusplus
}
#endif

#endif