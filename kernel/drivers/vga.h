#ifndef VGA_H
#define VGA_H

#define VMEM_ADDR 0xb8000
#define ROWS 25
#define COLS 80

#include "../util.h"

enum VGA_COLORS
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GRAY,
    GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    YELLOW,
    WHITE
};

u8 make_color(u8 text, u8 background);

u16 get_cursor_pos();
void set_cursor_pos(u8 x, u8 y);

void clear_screen();
void print(char *msg, u8 color);
void print_at(char *msg, u8 x, u8 y, u8 color);

#endif // VGA_H
