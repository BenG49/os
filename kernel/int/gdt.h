// helpful:
// https://stackoverflow.com/questions/23978486/far-jump-in-gdt-in-bootloader
#ifndef GDT_H
#define GDT_H

#include "../../util.h"
#include "../../drivers/vga.h"

#define ENTRIES 5

__attribute__((sysv_abi))
extern void gdt_asm(uint64_t *gdtr);

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
