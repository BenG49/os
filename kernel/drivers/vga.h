#ifndef VGA_H
#define VGA_H

#define VIDEO_ADDR 0xb8000
#define ROWS 25
#define COLS 80
#define SCREEN_SIZE 2000

#define COLOR 0x03

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

void clear();
void print(char *msg);
void scroll();

#endif // VGA_H
