#ifndef IDT_H
#define IDT_H

#include "../ports.h"
#include "../../drivers/vga.h"
#include "../../lib/mem.h"

// external isr stubs from asm file
extern void exc0();
extern void exc1();
extern void exc2();
extern void exc3();
extern void exc4();
extern void exc5();
extern void exc6();
extern void exc7();
extern void exc8();
extern void exc9();
extern void exc10();
extern void exc11();
extern void exc12();
extern void exc13();
extern void exc14();
extern void exc15();
extern void exc16();
extern void exc17();
extern void exc18();

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

// vector offset conversion
#define IRQ0  32
#define IRQ1  33
#define IRQ2  34
#define IRQ3  35
#define IRQ4  36
#define IRQ5  37
#define IRQ6  38
#define IRQ7  39
#define IRQ8  40
#define IRQ9  41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

#define INTERRUPT_COUNT 0x100

/**
 * Defined for each interrupt in vector table
 * 
 * offset       entry point of routine
 * selector     points to descriptor in GDT
 * flags
 *      0-3: gate type (0xe = 32 bit interrupt gate)
 *      4:   set to 0 for interrupt/trap gate (zero in long mode)
 *      5-6: privilege lvl (0=kernel)
 *      7:   interrupt present
 * ist          unused
 */
typedef struct
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist;        // only low 3 bits are used
    uint8_t flags;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t zero;
} __attribute__((packed)) idt_gate;

typedef struct
{
    uint16_t size;
    uint64_t offset;
} __attribute__((packed)) idt_register;

void set_idt_gate(int n, uint64_t handler_addr);
void init_idt();

#endif // IDT_H
