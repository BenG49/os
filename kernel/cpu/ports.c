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
