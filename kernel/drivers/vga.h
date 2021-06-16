#ifndef VGA_H
#define VGA_H

#define VIDEO_ADDR 0xb8000
#define ROWS 25
#define COLS 80
#define SCREEN_SIZE 2000

#define WHITE_ON_BLACK 0x0f
#define BLANK 0x0f20

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

int make_color(int text, int back);
void clear();
void set_cursor_pos(int x, int y);
void newline();
void print(char *msg, int color);
void scroll();

#endif // VGA_H
