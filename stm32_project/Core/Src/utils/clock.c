#include "clock.h"
#include "main.h"

clock_time_t current_time = 0;

struct timer delay_timer = {0};

void delay(uint16_t delay_time) // ms
{
	timer_set(&delay_timer, delay_time);
	while(!timer_expired(&delay_timer));
}
