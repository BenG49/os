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

void pic_eoi(uint8_t irq)
{
    // irq also came from PIC2 if > 7
    // with offset 40
    if (irq >= 40)
    {
        outb(PIC2_CMD, PIC_EOI);
    }
    
    outb(PIC1_CMD, PIC_EOI);
}

void log_char(char c)
{
    outb(COM1, c);
}

void log(char *str)
{
    int i = 0;
    while (str[i])
        log_char(str[i++]);
}

void log_int(int n, int base)
{
    if (base == 16)
    {
        log_char('0');
        log_char('x');
    }

    if (n == 0)
    {
        log_char('0');
        return;
    }

    char tmpb[21];
    int i = 0;

    while (n > 0)
    {
        tmpb[i++] = "0123456789abcdef"[n % base];
        n /= base;
    }

    while (i >= 0)
        log_char(tmpb[--i]);
}
