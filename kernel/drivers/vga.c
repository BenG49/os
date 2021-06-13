#include "vga.h"
#include "ports.h"

u8 make_color(u8 text, u8 background)
{
    return (background << 4) + text;
}

u16 get_cursor_pos()
{
    outb(VGA_INDEX, CURSOR_LOW);
    u16 pos = inb(VGA_DATA);
    outb(VGA_INDEX, CURSOR_HIGH);
    pos += inb(VGA_DATA) << 8;
    return pos;
}

void set_cursor_pos(u8 x, u8 y)
{
    u16 pos = y * COLS + x;
    outb(VGA_INDEX, CURSOR_LOW);
    outb(VGA_DATA, pos & 0xff);
    outb(VGA_INDEX, CURSOR_HIGH);
    outb(VGA_DATA, (pos >> 8) & 0xff);
}

void clear_screen()
{
    u16 screen_size = COLS * ROWS;
    u8 *data = (u8*)(VMEM_ADDR);

    for (u16 i = 0; i < screen_size; ++i)
    {
        data[i*2] = ' ';
        data[i*2+1] = 0x0f;
    }

    set_cursor_pos(0, 0);
}

void print(char *msg, u8 color)
{
    u8 *data = (u8*)(VMEM_ADDR + get_cursor_pos() * 2);
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
