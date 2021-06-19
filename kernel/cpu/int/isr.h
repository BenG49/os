#ifndef ISR_H
#define ISR_H

#include <stdint.h>
#include "../ports.h"
#include "../../drivers/vga.h"

#define INTERRUPT_COUNT 0x100

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

// used to get register values from pushad in asm
typedef struct 
{
    // pushed in asm
    uint32_t ds;
    // pushed by pushad
    uint32_t edi, esi, ebp, useless, ebx, edx, ecx, eax;
    // data pushed by isr
    uint32_t int_no, err_code;
    // auto pushed by cpu
    uint32_t eip, cs, eflaps, esp, ss;
} __attribute__((packed)) stack_regs;

// define function that will handle isr
typedef void (*handler)(stack_regs*);

void isr_handler(stack_regs *regs);
void set_handler(int n, handler h);

#endif // ISR_H
