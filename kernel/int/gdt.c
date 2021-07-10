#include "gdt.h"

static gdt_entry entries[ENTRIES];

static gdt_entry make_entry(
    uint32_t base,
    uint32_t limit,
    uint8_t ring,
    bool code,
    bool tss,
    bool read_write,
    bool page_granularity,
    bool dir)
{
    uint8_t access = 0;

    if (read_write)
        access |= (1 << 1); // read/write bit
    if (dir)
        access |= (1 << 2); // direction bit
    if (code)
        access |= (1 << 3); // executable bit
    if (!tss)
        access |= (1 << 4); // descriptor type
    if (ring <= 3)
        access |= (ring << 5); // privl
    
    access |= (1 << 7); // present bit

    uint8_t granularity = ((limit >> 16) & 0xf); // top 4 bits of limit

    if (code)
        granularity |= (1 << 5); // L bit
    if (page_granularity)
        granularity |= (1 << 7); // granularity bit
    
    gdt_entry out = {
        .limit       = (limit & 0xffff),
        .base_low    = (base & 0xffff),
        .base_mid    = ((base >> 16) & 0xff),
        .access      = access,
        .granularity = granularity,
        .base_hi     = ((base >> 24) & 0xff)
    };

    return out;
}

void init_gdt()
{
    entries[0] = (gdt_entry) {}; // null entry
    // kernel code segment (0x8)
    entries[1] = make_entry(0, 0, 0, true, false, true, false, false);
    // kernel data segment (0x10)
    entries[2] = make_entry(0, 0, 0, false, false, true, false, true);

    // user code segment (0x1b)
    entries[3] = make_entry(0, 0, 3, true, false, true, false, false);
    // user data segment (0x23)
    entries[4] = make_entry(0, 0, 3, false, false, true, false, false);

    gdtr gdt_reg = {
        .size = (uint16_t)(sizeof(entries) - 1),
        .offset = (size_t)entries
    };

    put_uint((uint64_t)&gdt_reg, 16);
    newline();

    gdt_asm((uint64_t *)&gdt_reg);

    puts("GDT loaded at ");
    put_uint((uint64_t)&gdt_reg, 16);
    newline();
}
