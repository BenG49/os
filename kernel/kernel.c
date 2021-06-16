#include "drivers/vga.h"
#include "cpu/idt.h"
#include "cpu/timer.h"

int kernel_main()
{
    init_idt();
    init_timer(50);
    clear();
    print("welcome to hell", make_color(RED, BLACK));
    newline();

    print("</kernel>\n", make_color(RED, BLACK));
}
