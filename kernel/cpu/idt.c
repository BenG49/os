#include "idt.h"

idt_gate idt[INTERRUPT_COUNT];
idt_register idt_reg;

void set_idt_gate(int n, uint32_t handler_addr)
{
    idt[n].offset1 = (uint16_t)(handler_addr & 0xffff);
    idt[n].offset2 = (uint16_t)((handler_addr >> 16) & 0xffff);

    idt[n].zero = 0;
    /* way back in bootsect.asm, this is the offset of the code
       segment, which is far jumped to (bootsect.asm:43) */
    idt[n].selector = 0x08;
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
    memset(&idt, 0, sizeof(idt_gate) * INTERRUPT_COUNT);
    PIC_init();

    // init idt gates
    set_idt_gate(IRQ0,  (uint32_t)isr0);
    set_idt_gate(IRQ1,  (uint32_t)isr1);
    set_idt_gate(IRQ2,  (uint32_t)isr2);
    set_idt_gate(IRQ3,  (uint32_t)isr3);
    set_idt_gate(IRQ4,  (uint32_t)isr4);
    set_idt_gate(IRQ5,  (uint32_t)isr5);
    set_idt_gate(IRQ6,  (uint32_t)isr6);
    set_idt_gate(IRQ7,  (uint32_t)isr7);
    set_idt_gate(IRQ8,  (uint32_t)isr8);
    set_idt_gate(IRQ9,  (uint32_t)isr9);
    set_idt_gate(IRQ10, (uint32_t)isr10);
    set_idt_gate(IRQ11, (uint32_t)isr11);
    set_idt_gate(IRQ12, (uint32_t)isr12);
    set_idt_gate(IRQ13, (uint32_t)isr13);
    set_idt_gate(IRQ14, (uint32_t)isr14);
    set_idt_gate(IRQ15, (uint32_t)isr15);

    write_idt();
}
