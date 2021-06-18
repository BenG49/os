#include "vga.h"
// returns offset in pixels
static int get_cursor_offset()
{
    outb(VGA_INDEX, CURSOR_HIGH);
    int offset = inb(VGA_DATA) << 8;
    outb(VGA_INDEX, CURSOR_LOW);
    offset += inb(VGA_DATA);
    return offset;
}

// takes in offset in pixels
static void set_cursor_offset(int offset)
{
    outb(VGA_INDEX, CURSOR_LOW);
    outb(VGA_DATA, (uint8_t)(offset & 0xff));
    outb(VGA_INDEX, CURSOR_HIGH);
    outb(VGA_DATA, (uint8_t)((offset >> 8) & 0xff));
}

void set_cursor_pos(int x, int y) { set_cursor_offset(y * COLS + x); }

void scroll()
{
    uint16_t *row = (uint16_t*)(VIDEO_ADDR + COLS);

    for (int i = 0; i < ROWS; ++i)
    {
        memcpy(row - COLS, row, COLS);
        row += COLS;
    }

    row = (uint16_t*)(VIDEO_ADDR + (SCREEN_SIZE - COLS) * 2);

    for (int i = 0; i < COLS; ++i)
    {
        row[i] = BLANK;
    }
}

static int print_char(char c, int color, int offset)
{
    if (c == '\b' && offset > 0)    // backspace
    {
        --offset;
        print_char(' ', color, offset);
    }
    else if (c == '\t') // 4 spaces (best tab spacing)
        offset = (offset + 4) & 0b11111111100;
    else if (c == '\r') // carrige return
        offset = offset % COLS;
    else if (c == '\n') // newline
        offset += COLS - (offset % COLS);
    else if (c >= ' ')  // printable character
    {
        if (offset >= SCREEN_SIZE)
        {
            scroll();
            offset -= COLS;
        }

        uint8_t *addr = (uint8_t*)(VIDEO_ADDR + offset * 2);
        addr[0] = c;
        addr[1] = color;
        ++offset;
    }

    set_cursor_offset(offset);
    return offset;
}

/********************
 * PUBLIC FUNCTIONS *
 ********************/

void clear()
{
    uint16_t *data = (uint16_t*)VIDEO_ADDR;

    for (uint16_t i = 0; i < SCREEN_SIZE; ++i)
        data[i] = BLANK;

    set_cursor_offset(0);
}

void putchar(char c)
{
    print_char(c, WOB, get_cursor_offset());
}

void puts_color(char *str, int color)
{
    int px_offset = get_cursor_offset();
    // no way anyone's going past 2^16, right?
    uint16_t i = 0;

    while (str[i] != 0)
        px_offset = print_char(str[i++], color, px_offset);
}

void puts(char *str)
{
    puts_color(str, WOB);
}

// more efficient than itoa, thanks to pitust from osdev discord
void putint(int n, int base)
{
    char tmpb[21];
    int i = 0;

    while (n > 0)
    {
        tmpb[i++] = "0123456789abcdef"[n % base];
        n /= base;
    }

    while (i >= 0)
        putchar(tmpb[i--]);
}

int make_color(int text, int back)
{
    return (int)((back << 4) | text);
}

void newline()
{
    int px_offset = get_cursor_offset();
    px_offset += COLS - (px_offset % COLS);
    set_cursor_offset(px_offset);
}
