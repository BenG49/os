#ifndef GDT_H
#define GDT_H

#include "../../util.h"

typedef struct
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t lim_flags;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry;

typedef struct
{
    uint16_t size;
    uint64_t offset;
} __attribute__((packed)) gdt_desc;

void init_gdt();

#endif // GDT_H
