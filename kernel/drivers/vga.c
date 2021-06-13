#include "vga.h"
#include "ports.h"

u16 get_cursor_pos()
{
    u16 pos;
    outb(VGA_INDEX, CURSOR_LOW);
    pos += inb(VGA_DATA);
    outb(VGA_INDEX, CURSOR_HIGH);
    pos += (u16)(inb(VGA_DATA) << 8);
    return pos;
}

void set_cursor_pos(u8 x, u8 y)
{
    u16 pos = x * COLS + y;
    outb(VGA_INDEX, CURSOR_LOW);
    outb(VGA_DATA, pos & 0xff);
    outb(VGA_INDEX, CURSOR_HIGH);
    outb(VGA_DATA, (pos >> 8) & 0xff);
}

void print_char(char c, u8 color)
{
    u8 *data = VGA_INDEX + get_cursor_pos() * 2;
    data[0] = c;
    data[1] = color;
}

void clear_screen()
{
    u16 screen_size = COLS * ROWS;
    u8 *data = VGA_INDEX;

    for (int i = 0; i < screen_size; ++i)
    {
        data[i*2] = ' ';
        data[i*2+1] = WHITE_BLACK;
    }

    set_cursor_pos(0, 0);
}

void print(char *msg, u8 color)
{
    u8 *data = get_cursor_pos() * 2;
    char *str = msg;

    while (*str != '\0')
    {
        *data = *str;
        ++data;
        *data = color;
        ++data;
        ++str;
    }
}

void print_at(char *msg, u8 x, u8 y, u8 color)
{
    set_cursor_pos(x, y);
    print(msg, color);
}
