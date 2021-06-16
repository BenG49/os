#ifndef IDT_H
#define IDT_H

#define INTERRUPT_COUNT 0x100

#include "../util.h"

// external isr stubs from asm file
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

/**
 * Defined for each interrupt in vector table
 * 
 * offset       entry point of routine
 * selector     points to descriptor in GDT
 * flags
 *      0-3: gate type (0xe = 32 bit interrupt gate)
 *      4:   set to 0 for interrupt/trap gate
 *      5-6: privilege lvl (0=kernel)
 *      7:   interrupt present
 */
typedef struct
{
    uint16_t offset1;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t offset2;
// packed has struct vars as close as possible
} __attribute__((packed)) idt_gate;

typedef struct
{
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) idt_register;

void set_idt_gate(int n, uint32_t handler_addr);
void write_idt();
void init_idt();

#endif // IDT_H
