#include "ports.h"

uint8_t inb(uint16_t port)
{
    uint8_t out;

    __asm__("inb %1, %0"
           :"=a"(out)
           :"dN"(port));
    return out;
}

void outb(uint16_t port, uint8_t data)
{
    __asm__("outb %1, %0"
         ::"dN"(port)
           ,"a"(data));
}

uint16_t inw(uint16_t port)
{
    uint16_t out;

    __asm__("inw %1, %0"
           :"=a"(out)
           :"dN"(port));
    return out;
}

void outw(uint16_t port, uint16_t data)
{
    __asm__("outw %1, %0"
          ::"dN"(port)
           ,"a"(data));
}
