#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#include "../int/idt.h"
#include "../sys/ports.h"

#define PIT_FREQ 1193182
#define MIN_FREQ 18
#define PIT_CH0  0x40

// passed in frequency in hertz
void init_timer(uint32_t freq);
int get_ms();

#endif // TIMER_H
