#include "timer.h"

static uint64_t tick;
static uint32_t f;

static void timer_callback(const stack *regs) { ++tick; }

void init_timer(uint32_t freq)
{
    if (freq > MIN_FREQ)
    {
        uint32_t divisor = (uint32_t)(PIT_FREQ / freq);

        if (divisor > 0xffff)
            divisor = 0;
        
        uint8_t l = (uint8_t)(divisor & 0xff);
        uint8_t h = (uint8_t)(divisor >> 8);

        asm volatile("cli");

        outb(0x43, 0x36);
        outb(PIT_CH0, l);
        outb(PIT_CH0, h);

        asm volatile("sti");
    } else
        freq = 0x10000;

    f = PIT_FREQ / freq;
    tick = 0;

    set_handler(PIC_OFFSET, timer_callback);

    printf("PIT initialized to %uHz\n", f);
}

int get_ms()
{
    return tick / f;
}
