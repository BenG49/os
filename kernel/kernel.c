#include "drivers/keyboard.h"
#include "cpu/idt.h"
#include "cpu/timer.h"

int kernel_main()
{
    init_idt();
    init_keyboard();
    init_timer(1);
    clear();
    print("welcome to hell", make_color(RED, BLACK));
    newline();

    print("</kernel>\n", make_color(RED, BLACK));

    return 0;
}
