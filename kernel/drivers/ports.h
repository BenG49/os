#ifndef PORTS_H
#define PORTS_H

#define VGA_INDEX   0x3d4
#define VGA_DATA    0x3d5

#define CURSOR_HIGH 0x0e
#define CURSOR_LOW  0x0f

// from osdev wiki
// PIC ports
#define PIC1        0x20
#define PIC1_CMD    PIC1
#define PIC1_DATA  (PIC1+1)
#define PIC2        0xa0
#define PIC2_CMD    PIC2
#define PIC2_DATA  (PIC2+1)
#define PIC_EOI     0x20

#include "../util.h"

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t data);
uint16_t inw(uint16_t port);
void outw(uint16_t port, uint16_t data);

// send end of interrupt
void pic_eoi(uint8_t irq);

#endif // PORTS_H
