#include "drivers/vga.h"
#include "cpu/idt.h"

int kernel_main()
{
    init_idt();
    clear();
    print("welcome to hell", make_color(RED, BLACK));
    __asm__ ("int $0x4");
}
