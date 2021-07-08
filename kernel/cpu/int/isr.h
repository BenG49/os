#ifndef ISR_H
#define ISR_H

#include <stdint.h>

#include "idt.h"
#include "../ports.h"
#include "../sys.h"
#include "../../drivers/vga.h"

// define function that will handle isr
typedef void (*handler)(registers*);

void isr_handler(registers *regs);
void set_handler(int n, handler h);

#endif // ISR_H
