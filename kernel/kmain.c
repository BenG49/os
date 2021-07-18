#include "kmain.h"

void kmain(struct stivale2_struct *tags)
{
    struct stivale2_struct_tag_framebuffer *framebuffer;
    framebuffer = get_tag(tags, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);

    struct stivale2_struct_tag_terminal *terminal;
    terminal = get_tag(tags, STIVALE2_STRUCT_TAG_TERMINAL_ID);

    struct stivale2_struct_tag_memmap *memmap;
    memmap = get_tag(tags, STIVALE2_STRUCT_TAG_MEMMAP_ID);

    if (framebuffer == NULL || terminal == NULL || memmap == NULL)
        for (;;) asm volatile("hlt");

    init_pmm(memmap, 1);
    init_tty(framebuffer);
    debug_ok("PMM initialized");

    print_pmm(memmap);

    init_idt();

    init_timer(1);
    init_keyboard();

    for (;;) asm volatile("hlt");
}
