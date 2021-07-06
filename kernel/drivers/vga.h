#ifndef VGA_H
#define VGA_H

#include "../../boot/stivale_util.h"
#include "../lib/string.h"

void init_vga(struct stivale2_struct *stivale2_struct);
// void (*term_write)(const char *string, size_t length);

void putc(char c);
void puts(const char *str);

#endif // VGA_H
