#include "kernel.h"

void _start(struct stivale2_struct *stivale2_struct)
{
    init_vga(stivale2_struct);

    init_idt();

    puts("lol");

    asm("int $0x3");
    // init_keyboard();
    // init_timer(1);
}
