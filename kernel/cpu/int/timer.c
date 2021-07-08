#include "timer.h"

uint32_t tick;
uint32_t f;

// static void timer_callback(registers *regs) { ++tick; }
static void timer_callback(registers *regs)
{
    ++tick;
    log_int(tick, 10);
    putc('a');
}

// freq 1 = 18.222hz
void init_timer(uint32_t frequency)
{
    // set isr callback
    set_handler(IRQ0, &timer_callback);

    // set frequency
    if (frequency != 1)
    {
        uint32_t divisor = PIT_FREQ / frequency;
        cli();

        // divisor of 0 used to specify 65536
        if (divisor > 0xffff)
            divisor = 0;

        uint8_t l = (uint8_t)(divisor & 0xff);
        uint8_t h = (uint8_t)((divisor > 8) & 0xff);

        // set command
        outb(0x43, 0x36);
        outb(PIT_CH0, l);
        outb(PIT_CH0, h);

        sti();
    } else
        frequency = 65536;

    f = PIT_FREQ / frequency;
    tick = 0;

    puts("PIT initialized to ");
    put_uint(f, 10);
    puts("Hz");
    newline();
}

uint32_t get_seconds()
{
    return tick / f;
}
