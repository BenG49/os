#include "ports.h"

u8 inb(u16 port)
{
    u8 out;

    __asm__("inb %1, %0"
           :"=a"(out)
           :"dN"(port));
    return out;
}

void outb(u16 port, u8 data)
{
    __asm__("outb %1, %0"
         ::"dN"(port)
           ,"a"(data));
}

u16 inw(u16 port)
{
    u16 out;

    __asm__("inw %1, %0"
           :"=a"(out)
           :"dN"(port));
    return out;
}

void outw(u16 port, u16 data)
{
    __asm__("outw %1, %0"
          ::"dN"(port)
           ,"a"(data));
}
