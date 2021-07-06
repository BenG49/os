#ifndef KERNEL_H
#define KERNEL_H

#include "drivers/vga.h"

#include "cpu/int/gdt.h"
#include "cpu/int/idt.h"
#include "cpu/int/timer.h"
#include "drivers/keyboard.h"
#include "util.h"

void _start();

#endif // KERNEL_H
