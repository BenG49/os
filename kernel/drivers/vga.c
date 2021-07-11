#include "vga.h"

static term_write term;
/*
pitch = bytes per row
*/
// static struct stivale2_struct_tag_framebuffer framebuffer;

static int height, width, pitch, bpp;
static uint32_t *framebuffer;

void init_vga(term_write t, struct stivale2_struct_tag_framebuffer *buf)
{
    term = t;

    height = buf->framebuffer_height;
    width = buf->framebuffer_width;
    pitch = buf->framebuffer_pitch;
    bpp = buf->framebuffer_bpp;
    framebuffer = (uint64_t *)buf->framebuffer_addr;

    term("VGA initialized\n", 17);
}

void puts(const char *str)
{
    term(str, strlen(str));
}

void putc(char c)
{
    term(&c, 1);
}

void put_int(int n, int base)
{
    if (base < 2 || base > 16)
        return;
    
    if (n < 0)
    {
        putc('-');
        n = -n;
    }

    if (base == 16)
    {
        putc('0');
        putc('x');
    }

    if (n == 0)
    {
        putc('0');
        return;
    }

    char tmpb[21];
    int i = 0;

    while (n > 0)
    {
        tmpb[i++] = "0123456789abcdef"[n % base];
        n /= base;
    }

    --i;

    while (i >= 0)
        putc(tmpb[i--]);
}

void put_uint(size_t n, int base)
{
    if (base < 2 || base > 16)
        return;
    
    if (n < 0) n = -n;

    if (base == 16)
    {
        putc('0');
        putc('x');
    }

    if (n == 0)
    {
        putc('0');
        return;
    }

    char tmpb[21];
    int i = 0;

    while (n > 0)
    {
        tmpb[i++] = "0123456789abcdef"[n % base];
        n /= base;
    }

    --i;

    while (i >= 0)
        putc(tmpb[i--]);
}

/*void printf(const char *fmt, ...)
{
    int tmp;
    va_list arg;
    va_start(arg, fmt);

    for (const char *c = fmt; *c != 0; ++c)
    {
        if (*c != '%')
        {
            putc(*c);
            continue;
        }

        ++c; // move past '%'

        switch (*c)
        {
            case 'c':
                tmp = va_arg(arg, int);
                if (tmp >= 0 && tmp < 0x100)
                    putc((char)tmp);
                break;
            case 'd':
                put_int(va_arg(arg, int), 10);
                break;
            // case 'e':
            // case 'f': // TODO: add put_float
            case 'o':
                put_int(va_arg(arg, int), 8);
                break;
            case 's':
                puts(va_arg(arg, const char *));
                break;
            case 'u':
                put_uint(va_arg(arg, int), 10);
                break;
            case 'x':
                put_int(va_arg(arg, int), 16);
                break;
            case '%':
                putc('%');
                break;
        }

        va_end(arg);
    }
}*/

void newline()
{
    puts("\n");
}

/* GRAPHICS FUNCTIONS */

/*static px make_px(color c)
{
    uint64_t out = 0;

    out |= ((c.r << framebuffer.red_mask_shift) & framebuffer.red_mask_size);
    out |= ((c.g << framebuffer.green_mask_shift) & framebuffer.green_mask_size);
    out |= ((c.b << framebuffer.blue_mask_shift) & framebuffer.blue_mask_size);

    int shift = 64 - framebuffer.framebuffer_bpp;

    return (px) {
        out << shift,
        shift
    };
}

void put_px(unsigned int x, unsigned int y, color c)
{
    if (x > framebuffer.framebuffer_width)
        return;
    if (y > framebuffer.framebuffer_height)
        return;

    px p = make_px(c);

    uint64_t *addr = (uint64_t *)framebuffer.framebuffer_addr;
    int bytespp = framebuffer.framebuffer_bpp / 8;

    addr += framebuffer.framebuffer_pitch * y + bytespp * x;

    *addr = p.data >> p.shift;
}*/
