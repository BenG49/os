#include "ports.h"

uint8_t inb(uint16_t port)
{
    uint8_t out;

    asm("inb %1, %0"
           :"=a"(out)
           :"dN"(port));
    return out;
}

void outb(uint16_t port, uint8_t data)
{
    asm("outb %1, %0"
         ::"dN"(port)
           ,"a"(data));
}

uint16_t inw(uint16_t port)
{
    uint16_t out;

    asm("inw %1, %0"
           :"=a"(out)
           :"dN"(port));
    return out;
}

void outw(uint16_t port, uint16_t data)
{
    asm("outw %1, %0"
          ::"dN"(port)
           ,"a"(data));
}

void logc(char c)
{
    outb(COM1, c);
}

void logs(char *str)
{
    int i = 0;
    while (str[i])
        logc(str[i++]);
}

void log_int(int n, int base)
{
    if (base < 2 || base > 16)
        return;

    if (base == 16)
    {
        logc('0');
        logc('x');
    }

    if (n == 0)
    {
        logc('0');
        return;
    }

    char tmpb[21];
    int i = 0;

    while (n > 0)
    {
        tmpb[i++] = "0123456789abcdef"[n % base];
        n /= base;
    }

    --i;

    while (i >= 0)
        logc(tmpb[i--]);
}

void pic_eoi(uint8_t irq)
{
    // irq also came from PIC2 if >= 8
    if (irq >= 8)
    {
        outb(PIC2_CMD, PIC_EOI);
    }
    
    outb(PIC1_CMD, PIC_EOI);
}

void pic_set_mask(uint8_t irq)
{
    uint16_t port;
    uint8_t value;

    if (irq < 8)
        port = PIC1_DATA;
    else
    {
        port = PIC2_DATA;
        irq -= 8;
    }

    value = inb(port) | (1 << irq);
    outb(port, value);
}

void pic_clear_mask(uint8_t irq)
{
    uint16_t port;
    uint8_t value;

    if (irq < 8)
        port = PIC1_DATA;
    else
    {
        port = PIC2_DATA;
        irq -= 8;
    }

    value = inb(port) & ~(1 << irq);
    outb(port, value);
}

void pic_clear_masks()
{
    inb(PIC1_DATA);
    outb(PIC1_DATA, 0x00);

    inb(PIC2_DATA);
    outb(PIC2_DATA, 0x00);
}
