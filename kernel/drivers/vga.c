#include "vga.h"
#include "ports.h"

void scroll();

int get_x(int px_offset) { return px_offset % COLS; }
int get_y(int px_offset) { return px_offset / COLS; }

// returns offset in pixels
int get_cursor_offset()
{
    outb(VGA_INDEX, CURSOR_LOW);
    int offset = inb(VGA_DATA);
    outb(VGA_INDEX, CURSOR_HIGH);
    offset += (inb(VGA_DATA) << 8);
    return offset;
}

// takes in offset in pixels
void set_cursor_offset(int offset)
{
    outb(VGA_INDEX, CURSOR_LOW);
    outb(VGA_DATA, offset & 0xff);
    outb(VGA_INDEX, CURSOR_HIGH);
    outb(VGA_DATA, (offset >> 8) & 0xff);
}

void set_cursor_pos(int x, int y) { set_cursor_offset(y * COLS + x); }

int print_char(char c, int x, int y)
{
    if (c == 0x8)       // backspace
        --x;
    else if (c == '\t')  // 4 spaces
        x = (x + 4) & 0b11111100;
    else if (c == '\r')
        x = 0;
    else if (c == '\n')
    {
        x = 0;
        ++y;
    }
    else if (c > ' ')
    {
        if (x >= COLS)
        {
            x = 0;
            ++y;
        }

        u16 *addr;
        addr = VIDEO_ADDR + ((y * COLS + x) * 2);
        *addr = (COLOR << 8) | c;
        ++x;
    }

    set_cursor_pos(x, y);
    return (y * 80 + x);
}

/********************
 * PUBLIC FUNCTIONS *
 ********************/

void clear()
{
    u16 *data = (u16*)VIDEO_ADDR;

    for (u16 i = 0; i < SCREEN_SIZE; ++i)
        data[i] = (0x0f << 8) | ' ';

    set_cursor_offset(0);
}

void print(char *str)
{
    int px_offset = get_cursor_offset();
    int i = 0;

    while (str[i])
    {
        // print_char(str[i++], i, 0);
        px_offset = print_char(str[i++], get_x(px_offset), get_y(px_offset));
    }
}

void scroll()
{
    u16 *row = (u16*)(VIDEO_ADDR + COLS);
    u16 blank = ' ' + 0x000f;

    for (int i = 0; i < ROWS; ++i)
    {
        _memcpy(row, row - COLS, COLS);
        row += COLS;
    }

    // row = (u16*)(VIDEO_ADDR + COLS * (ROWS - 1));

    for (int i = 0; i < COLS; ++i)
    {
        row[i] = blank;
    }
}
