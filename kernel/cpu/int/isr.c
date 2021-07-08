#include "isr.h"

handler handlers[INTERRUPT_COUNT];

char *messages[] = {
    "Division by zero exception",
    "Debug exception",
    "Non maskable interrupt",
    "Breakpoint exception",
    "Into detected overflow",
    "Out of bounds exception",
    "Invalid opcode exception",
    "No coprocessor exception",
    "Double fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown exception",
    "Coprocessor fault",
    "Alignment check exception",
    "Machine check exception",
    "Unknown exception"
};

void isr_handler(registers *regs)
{
    // exception
    if (regs->isr_num < 32)
    {
        logs("Exception: ");
        log_int(regs->isr_num, 10);
        logc('\n');
        int i = regs->isr_num;
        // didn't include messages for exceptions > 19
        if (i > 19)
            i = 19;
        
        puts(messages[i]);

        while (1) { asm("hlt"); }
    }

    // end interupt from PIC
    pic_eoi(regs->isr_num);

    // call interrupt/exception
    if (handlers[regs->isr_num] != 0)
        handlers[regs->isr_num](regs);
}

void set_handler(int n, handler h) { handlers[n] = h; }
