#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>

#define VGA_INDEX   0x3d4
#define VGA_DATA	0x3d5

#define CURSOR_HIGH 0x0e
#define CURSOR_LOW  0x0f

// PIC ports
#define PIC1		0x20
#define PIC1_CMD	PIC1
#define PIC1_DATA  (PIC1+1)
#define PIC2		0xa0
#define PIC2_CMD	PIC2
#define PIC2_DATA  (PIC2+1)
#define PIC_EOI	 0x20

#define COM1		0x3f8

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t data);
uint16_t inw(uint16_t port);
void outw(uint16_t port, uint16_t data);

// qemu logging
void logc(char c);
void logs(char *str);
// putint
void log_int(int n, int base);

// send end of interrupt
void pic_eoi(uint8_t irq);
void pic_set_mask(uint8_t irq);
void pic_clear_mask(uint8_t irq);
void pic_clear_masks();

#endif // PORTS_H