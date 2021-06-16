#ifndef VGA_H
#define VGA_H

#include "../cpu/ports.h"
#include "../util/string.h"
#include "../util/util.h"

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
// prints single char
void printc(char c, int color);
// wrapper function for itoa, uses 255 byte buffer
void printi(int n, int base, int color);
void print(char *msg, int color);
void scroll();

#endif // VGA_H
