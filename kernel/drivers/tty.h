// TODO: add double buffer once mem works
#ifndef TTY_H
#define TTY_H

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

#include <lib/font.h>
#include <lib/mem.h>
#include <boot/stivale2.h>

#define FONT_X 8
#define FONT_Y 16

typedef struct {
	uint8_t b;
	uint8_t g;
	uint8_t r;
	uint8_t a;
} __attribute__((packed)) color;

void init_tty(struct stivale2_struct_tag_framebuffer *buf);

// cursor functions to draw at different screen locations
void clear_cursor();
void draw_cursor();
void disable_cursor();
void enable_cursor();
void set_cursor(uint32_t x, uint32_t y);
void scroll();

// printing functions
void putc(char c);
void puts(const char *str);
void put_int(int n, int base);
void put_uint(size_t n, int base);
void printf(const char *fmt, ...);

// kernel ok debug print
void debug_ok(const char *str);
void debug_err(const char *str);

void set_color(color c);

#endif // TTY_H
