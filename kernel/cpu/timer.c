#include "timer.h"
#include "isr.h"
#include "../drivers/vga.h"

uint32_t tick = 0;

static void timer_callback(stack_regs regs)
{
    ++tick;
    print("Tick: ", WHITE_ON_BLACK);
    char buf[16];
    print(itoa(tick, buf, 16), WHITE_ON_BLACK);
    newline();
}

void init_timer(uint32_t frequency)
{
    // set callback
    set_handler(IRQ0, &timer_callback);

    // set frequency
    uint8_t divisor = PIT_FREQ / frequency;
    cli();

    // divisor of 0 used to specify 65535
    if (divisor == 0xffff)
        divisor = 0;

    outb(PIT_CH0, divisor & 0xff);
    outb(PIT_CH0, (divisor & 0xff00) >> 8);

    sti();
    return;
}
