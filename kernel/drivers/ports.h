// #ifndef PORTS_H
// #define PORTS_H

#define VGA_INDEX   0x3d4
#define VGA_DATA    0x3d5

#define CURSOR_HIGH 0x0e
#define CURSOR_LOW  0x0f

#include "../util.h"

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t data);
uint16_t inw(uint16_t port);
void outw(uint16_t port, uint16_t data);

// #endif // PORTS_H
