#ifndef ISR_H
#define ISR_H

#include "../util.h"

// used to get register values from pushad in asm
typedef struct 
{
    // pushed in asm
    uint32_t ds;
    // pushed by pushad
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    // data pushed by isr
    uint32_t int_no, err_code;
    // auto pushed by cpu?
    uint32_t eip, cs, eflaps, useresp, ss;
} __attribute__((packed)) stack_regs;


void isr_handler(stack_regs regs);

#endif // ISR_H
