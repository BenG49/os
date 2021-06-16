#ifndef TIMER_H
#define TIMER_H

#include "../util.h"

#define PIT_FREQ 1193182
#define PIT_CH0 0x40

void init_timer(uint32_t frequency);

#endif // TIMER_H
