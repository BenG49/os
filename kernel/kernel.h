#ifndef KERNEL_H
#define KERNEL_H

#include "drivers/vga.h"
#include "drivers/keyboard.h"

#include "cpu/int/idt.h"
#include "cpu/int/timer.h"

void kmain();

#endif // KERNEL_H
