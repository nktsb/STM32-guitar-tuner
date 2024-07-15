#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <stdint.h>

typedef int32_t clock_time_t;
extern  clock_time_t  current_time;

#define clock_time() current_time
#define clock_time_cb() current_time++;

void delay(uint16_t delay_time);

#endif /* __CLOCK_H__ */
