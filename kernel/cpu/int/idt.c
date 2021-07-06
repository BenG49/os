#include "idt.h"

static idt_gate idt[INTERRUPT_COUNT];
static idt_register idt_reg;

void set_idt_gate(int n, uint64_t handler_addr)
{
    idt[n].offset_low = (uint16_t)(handler_addr & 0xffff);
    idt[n].offset_mid = (uint16_t)((handler_addr >> 16) & 0xffff);
    idt[n].offset_high = (uint32_t)((handler_addr >> 32) & 0xffffffff);

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
    set_idt_gate(0,  (size_t)exc0);
    set_idt_gate(1,  (size_t)exc1);
    set_idt_gate(2,  (size_t)exc2);
    set_idt_gate(3,  (size_t)exc3);
    set_idt_gate(4,  (size_t)exc4);
    set_idt_gate(5,  (size_t)exc5);
    set_idt_gate(6,  (size_t)exc6);
    set_idt_gate(7,  (size_t)exc7);
    set_idt_gate(8,  (size_t)exc8);
    set_idt_gate(9,  (size_t)exc9);
    set_idt_gate(10, (size_t)exc10);
    set_idt_gate(11, (size_t)exc11);
    set_idt_gate(12, (size_t)exc12);
    set_idt_gate(13, (size_t)exc13);
    set_idt_gate(14, (size_t)exc14);
    set_idt_gate(15, (size_t)exc15);
    set_idt_gate(16, (size_t)exc16);
    set_idt_gate(17, (size_t)exc17);
    set_idt_gate(18, (size_t)exc18);

    // hardware interrupts
    set_idt_gate(IRQ0,  (size_t)isr0);
    set_idt_gate(IRQ1,  (size_t)isr1);
    set_idt_gate(IRQ2,  (size_t)isr2);
    set_idt_gate(IRQ3,  (size_t)isr3);
    set_idt_gate(IRQ4,  (size_t)isr4);
    set_idt_gate(IRQ5,  (size_t)isr5);
    set_idt_gate(IRQ6,  (size_t)isr6);
    set_idt_gate(IRQ7,  (size_t)isr7);
    set_idt_gate(IRQ8,  (size_t)isr8);
    set_idt_gate(IRQ9,  (size_t)isr9);
    set_idt_gate(IRQ10, (size_t)isr10);
    set_idt_gate(IRQ11, (size_t)isr11);
    set_idt_gate(IRQ12, (size_t)isr12);
    set_idt_gate(IRQ13, (size_t)isr13);
    set_idt_gate(IRQ14, (size_t)isr14);
    set_idt_gate(IRQ15, (size_t)isr15);

    idt_reg.size = (uint16_t)(sizeof(idt) * INTERRUPT_COUNT - 1);
    idt_reg.offset = (uint64_t)idt;

    asm("lidt %0" :: "m"(idt_reg) : "memory");
}
