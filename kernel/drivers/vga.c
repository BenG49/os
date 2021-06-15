#include "vga.h"
#include "ports.h"

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
    outb(VGA_DATA, (u8)(offset & 0xff));
    outb(VGA_INDEX, CURSOR_HIGH);
    outb(VGA_DATA, (u8)((offset >> 8) & 0xff));
}

void set_cursor_pos(int x, int y) { set_cursor_offset(y * COLS + x); }

void scroll()
{
    u16 *row = (u16*)(VIDEO_ADDR + COLS);

    for (int i = 0; i < ROWS; ++i)
    {
        _memcpy(row, row - COLS, COLS);
        row += COLS;
    }

    row = (u16*)(VIDEO_ADDR + COLS * (ROWS - 1));

    for (int i = 0; i < COLS; ++i)
    {
        row[i] = BLANK;
    }
}

static int print_char(char c, int color, int offset)
{
    // u8 *addr = (u8*)(VIDEO_ADDR + offset * 2);
    // addr[0] = c;
    // addr[1] = color;
    // set_cursor_offset(++offset);
    // return offset;

    /*if (c == 0x8 && offset > 0) // backspace
        --offset;
    else if (c == '\t') // 4 spaces (best tab spacing)
        offset = (offset + 4) & 0b11111100;
    else if (c == '\r') // carrige return
        offset = offset % COLS;
    else*/ if (c == '\n') // newline
        offset += COLS - (offset % COLS);
    else if (c >= ' ')  // printable character
    {
        if (offset >= SCREEN_SIZE)
        {
            scroll();
            offset -= COLS;
        }

        u8 *addr = (u8*)(VIDEO_ADDR + offset * 2);
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
    u16 *data = (u16*)VIDEO_ADDR;

    for (u16 i = 0; i < SCREEN_SIZE; ++i)
        data[i] = BLANK;
        // data[i] = ((color & 0xf) << 12) | 0xf00 | ' ';

    set_cursor_offset(0);
}

void print(const char *str, int color)
{
    int px_offset = get_cursor_offset();

    while (*str != 0)
        px_offset = print_char(*str++, color, px_offset);
}
