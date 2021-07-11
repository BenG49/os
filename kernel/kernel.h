#ifndef KERNEL_H
#define KERNEL_H

#include "drivers/keyboard.h"
#include "int/idt.h"
#include "int/timer.h"

void shell_cmd(char *cmd);

#endif
