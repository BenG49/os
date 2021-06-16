#include "isr.h"
#include "../drivers/ports.h"
#include "../drivers/vga.h"

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
    // pic_eoi(regs.int_no);

    char buf[32] = "recieved interrupt: ";
    print(buf, WHITE_ON_BLACK);
    print(itoa(regs.int_no, buf, 10), WHITE_ON_BLACK);
    newline();
}
