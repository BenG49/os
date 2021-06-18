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

void isr_handler(stack_regs *regs)
{
    // exception
    if (regs->int_no < 32)
    {
        log("Exception: ");
        log_int(regs->int_no, 10);
        log_char('\n');
        int i = regs->int_no;
        if (i > 19)
            i = 19;
        
        print(messages[i]);

        asm("hlt");
    }

    // end interupt from PIC
    pic_eoi((uint8_t)regs->int_no);

    // call interrupt/exception
    if (handlers[regs->int_no] != 0)
        handlers[regs->int_no](regs);
}

void set_handler(int n, handler h) { handlers[n] = h; }
