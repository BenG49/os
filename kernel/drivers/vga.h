#ifndef VGA_H
#define VGA_H

#include <stddef.h>
#include <stdarg.h>

#include "../lib/string.h"
#include "../../boot/stivale2.h"

typedef void (*term_write)(const char *string, size_t len);

typedef struct {
    int r, g, b;
} color;

typedef struct {
    uint64_t data;
    int shift;
} px;

void init_vga(term_write t, struct stivale2_struct_tag_framebuffer *framebuffer);

void puts(const char *str);
void putc(char c);
void put_int(int n, int base);
void put_uint(size_t n, int base);
// void printf(const char *fmt, ...);

void newline();

void put_px(unsigned int x, unsigned int y, color c);

#endif // VGA_H
