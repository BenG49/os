// #ifndef PORTS_H
// #define PORTS_H

#define VGA_INDEX   0x3d4
#define VGA_DATA    0x3d5

#define CURSOR_HIGH 0x0e
#define CURSOR_LOW  0x0f

#include "../util.h"

u8 inb(u16 port);
void outb(u16 port, u8 data);
u16 inw(u16 port);
void outw(u16 port, u16 data);

// #endif // PORTS_H
