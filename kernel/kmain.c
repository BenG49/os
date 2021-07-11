#include "kmain.h"

void kmain(struct stivale2_struct *tags)
{
    struct stivale2_struct_tag_framebuffer *framebuffer;
    framebuffer = get_tag(tags, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);

    struct stivale2_struct_tag_terminal *terminal;
    terminal = get_tag(tags, STIVALE2_STRUCT_TAG_TERMINAL_ID);

    if (framebuffer == NULL || terminal == NULL)
        for (;;) asm volatile("hlt");

    init_vga((void *)terminal->term_write, framebuffer);
    init_idt();
    init_timer(1);
    init_keyboard();

    // for some reason interrupt bit was cleared
    asm volatile("sti");

    for (;;) asm volatile("hlt");
}
