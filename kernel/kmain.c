#include "kmain.h"

void h(const stack *regs)
{
    puts("test\n");
}

void kmain(struct stivale2_struct *tags)
{
    struct stivale2_struct_tag_framebuffer *framebuffer;
    framebuffer = get_tag(tags, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);

    struct stivale2_struct_tag_terminal *terminal;
    terminal = get_tag(tags, STIVALE2_STRUCT_TAG_TERMINAL_ID);

    if (framebuffer == NULL || terminal == NULL)
        for (;;) { __asm__ volatile("hlt"); }

    init_vga((void *)terminal->term_write, framebuffer);
    // init_gdt();
    // init_idt();

    // set_handler(32, h);

    // asm volatile("int $32");
}
