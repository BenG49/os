#ifndef VGA_H
#define VGA_H

#define VMEM_ADDR 0xb8000
#define ROWS 25
#define COLS 80
#define WHITE_BLACK 0x0f
#define RED_WHITE   0xf4

#include "../util.h"

u16 get_cursor_pos();
void set_cursor_pos(u8 x, u8 y);

void print_char(char c, u8 color);
void clear_screen();
void print(char *msg, u8 color);
void print_at(char *msg, u8 x, u8 y, u8 color);

#endif // VGA_H
