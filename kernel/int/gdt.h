// helpful:
// https://stackoverflow.com/questions/23978486/far-jump-in-gdt-in-bootloader
#ifndef GDT_H
#define GDT_H

#include <stdint.h>
#include <stdbool.h>

#include "../drivers/vga.h"

#define ENTRIES 5

// access byte
#define READ_WRITE  0b00000010
#define DIR         0b00000100
#define EXECUTABLE  0b00001000
#define NONSYS_DESC 0b00010000
#define USER_PRIVL  0b01100000
#define PRESENT     0b10000000

// granularity
#define PAGE_GRANULARITY 0b10000000
#define CODE_GRANULARITY 0b00100000

__attribute__((sysv_abi))
extern void lgdt(size_t gdtr);

typedef struct
{
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_hi;
} __attribute__((packed)) gdt_entry;

typedef struct
{
    uint16_t size;
    uint64_t offset;
} __attribute__((packed)) gdtr;

void init_gdt();

#endif // GDT_H
