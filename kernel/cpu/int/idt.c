#include "idt.h"

static idt_gate idt[INTERRUPT_COUNT];
static idt_register idt_reg;

void set_idt_gate(int n, uint64_t handler_addr)
{
    idt[n].offset1 = (uint16_t)(handler_addr & 0xffff);
    idt[n].offset2 = (uint16_t)((handler_addr >> 16) & 0xffff);
    idt[n].offset3 = (uint32_t)((handler_addr >> 32) & 0xffffffff);

    // unused feature
    idt[n].ist = 0;

    idt[n].zero = 0;
    // this is the offset of the code segment
    idt[n].selector = 0x08;
    // gate type = 32 bit int, privilige lvl 0
    idt[n].flags = 0b10001110;
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
    // clear table
    // memset(&idt, 0, sizeof(idt_gate) * INTERRUPT_COUNT);
    // PIC_init();

    // init idt gates
    // exceptions
    set_idt_gate(0,  (uint64_t)exc0);
    set_idt_gate(1,  (uint64_t)exc1);
    set_idt_gate(2,  (uint64_t)exc2);
    set_idt_gate(3,  (uint64_t)exc3);
    set_idt_gate(4,  (uint64_t)exc4);
    set_idt_gate(5,  (uint64_t)exc5);
    set_idt_gate(6,  (uint64_t)exc6);
    set_idt_gate(7,  (uint64_t)exc7);
    set_idt_gate(8,  (uint64_t)exc8);
    set_idt_gate(9,  (uint64_t)exc9);
    set_idt_gate(10, (uint64_t)exc10);
    set_idt_gate(11, (uint64_t)exc11);
    set_idt_gate(12, (uint64_t)exc12);
    set_idt_gate(13, (uint64_t)exc13);
    set_idt_gate(14, (uint64_t)exc14);
    set_idt_gate(15, (uint64_t)exc15);
    set_idt_gate(16, (uint64_t)exc16);
    set_idt_gate(17, (uint64_t)exc17);
    set_idt_gate(18, (uint64_t)exc18);

    // hardware interrupts
    set_idt_gate(IRQ0,  (uint64_t)isr0);
    set_idt_gate(IRQ1,  (uint64_t)isr1);
    set_idt_gate(IRQ2,  (uint64_t)isr2);
    set_idt_gate(IRQ3,  (uint64_t)isr3);
    set_idt_gate(IRQ4,  (uint64_t)isr4);
    set_idt_gate(IRQ5,  (uint64_t)isr5);
    set_idt_gate(IRQ6,  (uint64_t)isr6);
    set_idt_gate(IRQ7,  (uint64_t)isr7);
    set_idt_gate(IRQ8,  (uint64_t)isr8);
    set_idt_gate(IRQ9,  (uint64_t)isr9);
    set_idt_gate(IRQ10, (uint64_t)isr10);
    set_idt_gate(IRQ11, (uint64_t)isr11);
    set_idt_gate(IRQ12, (uint64_t)isr12);
    set_idt_gate(IRQ13, (uint64_t)isr13);
    set_idt_gate(IRQ14, (uint64_t)isr14);
    set_idt_gate(IRQ15, (uint64_t)isr15);

    idt_reg.size = (uint16_t)(sizeof(idt) * INTERRUPT_COUNT - 1);
    idt_reg.offset = (uint64_t)idt;

    asm("lidt %0" :: "m"(idt_reg) : "memory");
}
