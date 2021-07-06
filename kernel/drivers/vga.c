#include "vga.h"

/*
pitch       = number of bytes in each row
bpp         = bits per pixel
mem_model   = 1=rgb, everything else undefined

_ mask      = bit mask for rgb value, ex: redmask = 0xff0000
_ shift     = bit shift for rgb value, ex: redshift = 16
*/
static struct stivale2_struct_tag_framebuffer *framebuffer_struct;
static void (*term_write)(const char *string, size_t length);

void init_vga(struct stivale2_struct *stivale2_struct)
{
    framebuffer_struct = get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);

    struct stivale2_struct_tag_terminal *terminal_struct;
    terminal_struct = get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_TERMINAL_ID);

    if (framebuffer_struct == NULL || terminal_struct == NULL)
    {
        // TODO: figure out how to handle this
    }

    term_write = (void *)terminal_struct->term_write;
}

// static void set_px(int x, int y, int r, int g, int b)
// {
//     void *ptr = (void *)framebuffer_struct->framebuffer_addr;

// }

void putc(char c)
{
    if (c == '\b')
    {
        char *buf = "\b \b";
        term_write(buf, 3);
        return;
    }

    char buf[2];

    buf[0] = c;
    buf[1] = '\0';

    term_write(buf, 1);
}

void puts(const char *str)
{
    term_write(str, strlen(str));
}
