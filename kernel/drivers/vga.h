#ifndef VGA_H
#define VGA_H

#include "../cpu/ports.h"
#include "../util/string.h"
#include "../util/mem.h"

#define VIDEO_ADDR 0xb8000
#define ROWS 25
#define COLS 80
#define SCREEN_SIZE 2000

// white on black
#define WOB 0x0f
// blank pixel
#define BLANK 0x0f20

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

int make_color(int text, int back);
void clear();
void set_cursor_pos(int x, int y);
void newline();

void putchar(char c);
void putint(int n, int base);
void puts(char *msg);
void puts_color(char *msg, int color);
void scroll();

#endif // VGA_H
