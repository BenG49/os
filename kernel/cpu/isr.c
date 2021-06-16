#include "isr.h"
#include "../drivers/ports.h"
#include "../drivers/vga.h"

handler handlers[INTERRUPT_COUNT];

const char *messages[] = {
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
    "Unknown interrupt exception",
    "Coprocessor fault",
    "Alignment check exception",
    "Machine check exception",
    "Reserved"
};

void isr_handler(stack_regs regs)
{
    // end interupt
    // TODO: fix this, for some reason causing interrupt loop
    pic_eoi((uint8_t)regs.int_no);

    print("Recieved interrupt: ", WHITE_ON_BLACK);
    char buf[16];
    print(itoa(regs.int_no, buf, 16), WHITE_ON_BLACK);

    if (regs.err_code != 0)
    {
        print(" error: ", WHITE_ON_BLACK);
        print(itoa(regs.err_code, buf, 10), WHITE_ON_BLACK);
    }

    newline();

    // call interrupt
    if (handlers[regs.int_no] != 0)
    {
        handlers[regs.int_no](regs);
    }
}

void set_handler(int n, handler h)
{
    handlers[n] = h;
}
