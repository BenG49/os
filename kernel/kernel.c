#include "kernel.h"

void kmain(struct stivale2_struct *stivale2_struct)
{
    init_vga(stivale2_struct);

    init_idt();
    init_timer(1);
    // init_keyboard();
}
