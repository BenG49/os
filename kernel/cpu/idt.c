#include "idt.h"
#include "../drivers/ports.h"

idt_gate idt[INTERRUPT_COUNT];
idt_register idt_reg;

void set_idt_gate(int n, uint32_t handler_addr)
{
    idt[n].offset1 = (uint16_t)(handler_addr & 0xffff);
    idt[n].offset2 = (uint16_t)(handler_addr >> 0xffff);

    idt[n].zero = 0;
    /* way back in bootsect.asm, this is the offset of the code
       segment, which is far jumped to (bootsect.asm:43) */
    idt[n].selector = 0x8;
    // gate type = 32 bit int, privilige lvl 0
    idt[n].flags = 0b10001110;
}

void write_idt()
{
    idt_reg.offset = (uint32_t)idt;
    idt_reg.size = (uint16_t)(sizeof(idt) * INTERRUPT_COUNT - 1);

    __asm__("lidt %0"
          ::"memory"(idt_reg));
}

// moves PIC interrupts to after CPU defined interrupts
// IBM did an oops and made them interfere in protected mode
static void PIC_init()
{
    uint8_t a1, a2;

    // save masks, whatever that means
    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);

    // init
    outb(PIC1_CMD, 0x11);
    outb(PIC2_CMD, 0x11);

    // set new offsets
    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);

    // do something
    outb(PIC1_DATA, 4);
    outb(PIC2_DATA, 2);
    outb(PIC1_DATA, 1);
    outb(PIC2_DATA, 1);

    // restore masks
    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);
}

void init_idt()
{
    // init idt gates
    set_idt_gate(0,  (uint32_t)isr0);
    set_idt_gate(1,  (uint32_t)isr1);
    set_idt_gate(2,  (uint32_t)isr2);
    set_idt_gate(3,  (uint32_t)isr3);
    set_idt_gate(4,  (uint32_t)isr4);
    set_idt_gate(5,  (uint32_t)isr5);
    set_idt_gate(6,  (uint32_t)isr6);
    set_idt_gate(7,  (uint32_t)isr7);
    set_idt_gate(8,  (uint32_t)isr8);
    set_idt_gate(9,  (uint32_t)isr9);
    set_idt_gate(10, (uint32_t)isr10);
    set_idt_gate(11, (uint32_t)isr11);
    set_idt_gate(12, (uint32_t)isr12);
    set_idt_gate(13, (uint32_t)isr13);
    set_idt_gate(14, (uint32_t)isr14);
    set_idt_gate(15, (uint32_t)isr15);
    set_idt_gate(16, (uint32_t)isr16);
    set_idt_gate(17, (uint32_t)isr17);
    set_idt_gate(18, (uint32_t)isr18);
    set_idt_gate(19, (uint32_t)isr19);
    set_idt_gate(20, (uint32_t)isr20);
    set_idt_gate(21, (uint32_t)isr21);
    set_idt_gate(22, (uint32_t)isr22);
    set_idt_gate(23, (uint32_t)isr23);
    set_idt_gate(24, (uint32_t)isr24);
    set_idt_gate(25, (uint32_t)isr25);
    set_idt_gate(26, (uint32_t)isr26);
    set_idt_gate(27, (uint32_t)isr27);
    set_idt_gate(28, (uint32_t)isr28);
    set_idt_gate(29, (uint32_t)isr29);
    set_idt_gate(30, (uint32_t)isr30);
    set_idt_gate(31, (uint32_t)isr31);

    write_idt();
    PIC_init();
}
