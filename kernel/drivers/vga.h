#ifndef VGA_H
#define VGA_H

#include "../../boot/stivale_util.h"
#include "../lib/string.h"

#include <stdbool.h>

void init_vga(struct stivale2_struct *stivale2_struct);
// void (*term_write)(const char *string, size_t length);

void putc(char c);
void puts(const char *str);
void put_uint(unsigned int n, int base);
void put_int(int n, int base);
void newline();

#endif // VGA_H
