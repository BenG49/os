#include "tty.h"

// constants
const color WHITE = { 255, 255, 255, 255 };
const color BLACK = { 0, 0, 0, 0 };

// pitch = bytes in row
int height, width, pitch, font_height;
static color *framebuffer;

int cursor_x = 0;
int cursor_y = 0;

static color text_color = { 255, 255, 255, 255 };

static bool cursor_on = true;

static void *get_cursor_ptr()
{
    return framebuffer + (cursor_y * width * FONT_Y) + (cursor_x * FONT_X);
}

static void cursor(color clr)
{
    color *c = get_cursor_ptr();

    for (int y = 0; y < FONT_Y; ++y)
    {
        for (int x = 0; x < FONT_X; ++x)
            *c++ = clr;

        c += width - FONT_X;
    }
}

void clear_cursor()
{
    if (cursor_on)
        cursor(BLACK);
}
void draw_cursor()
{
    if (cursor_on)
        cursor(WHITE);
}

void set_cursor(uint32_t x, uint32_t y)
{
    clear_cursor();

    cursor_x = x;
    cursor_y = y;

    draw_cursor();
}

void disable_cursor() { cursor_on = false; cursor(BLACK); }
void enable_cursor()  { cursor_on = true; draw_cursor(); }

static void plot_char(char ch, color c)
{
    clear_cursor();

    // normal characters
    if (ch > 0x1f)
    {
        // start framebuffer offset
        color *buf = get_cursor_ptr();
        uint8_t *char_ptr = font_bitmap[(int)ch];

        for (int y = 0; y < FONT_Y; ++y)
        {
            for (int x = FONT_X - 1; x >= 0; --x)
            {
                // if bit set
                if (((char_ptr[y] >> x) & 1) == 1)
                    *buf = c;

                ++buf;
            }

            buf += width - FONT_X;
        }

        ++cursor_x;

        if (cursor_x >= width)
            cursor_x = 0;
    }
    else if (ch == '\n')
    {
        ++cursor_y;
        cursor_x = 0;

        if (cursor_y >= font_height)
        {
            scroll();
            clear_cursor();
            --cursor_y;
        }
    }
    else if (ch == '\t')
    {
        cursor_x += 4;
        cursor_x &= ~(0b11);

        if (cursor_x >= width)
            cursor_x = 0;
    }
    else if (ch == '\b')
    {
        if (cursor_x > 0)
            --cursor_x;

        cursor(BLACK);
    }
    else if (ch == '\r')
    {
        cursor_x = 0;
    }

    draw_cursor();
}

void init_tty(struct stivale2_struct_tag_framebuffer *buf)
{
    framebuffer = (void *)buf->framebuffer_addr;

    height = buf->framebuffer_height;
    width = buf->framebuffer_width;
    pitch = buf->framebuffer_pitch;
    font_height = height / FONT_Y;

    // clear screen
    memset(framebuffer, 0, pitch * width);

    puts("[ ");
    plot_char('O', (color){.g = 255});
    plot_char('K', (color){.g = 255});
    puts(" ] ");

    plot_char('T', (color){ .r = 255 });
    plot_char('T', (color){ .g = 255 });
    plot_char('Y', (color){ .b = 255 });
    puts(" initialized\n");
}

void putc(char c)
{
    plot_char(c, text_color);
}

void puts(const char *str)
{
    while (*str)
        putc(*str++);
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

void printf(const char *format, ...)
{
    va_list arg;
    va_start(arg, format);

    while (*format)
    {
        if (*format != '%')
        {
            putc(*format++);
            continue;
        }

        // move past '%'
        ++format;

        // % at end of string
        if (*format == '\0')
            break;

        switch (*format++)
        {
            case 'c': putc(va_arg(arg, int));
                break;
            case 'd': put_int(va_arg(arg, int), 10);
                break;
            case 'o': put_uint(va_arg(arg, unsigned int), 8);
                break;
            case 's': puts(va_arg(arg, char *));
                break;
            case 'u': put_uint(va_arg(arg, unsigned int), 10);
                break;
            case 'x': put_uint(va_arg(arg, size_t), 16);
                break;
            // non-standard, binary format
            case 'b': put_uint(va_arg(arg, unsigned int), 2);
                break;
            case '%': putc('%');
                break;
        }
    }

    va_end(arg);
}

void debug_ok(const char *str)
{
    puts("[ ");
    plot_char('O', (color){.g = 255});
    plot_char('K', (color){.g = 255});
    puts(" ] ");

    puts(str);
    putc('\n');
}

// java flashbacks
void set_color(color c) { text_color = c; }

void scroll()
{
    clear_cursor();

    for (uint32_t i = width * FONT_Y; i < width * height; ++i)
    {
        framebuffer[i - width * 16] = framebuffer[i];
    }

    for (uint32_t i = width * (height - FONT_Y); i < width * height; ++i)
    {
        framebuffer[i] = BLACK;
    }

    draw_cursor();
}
