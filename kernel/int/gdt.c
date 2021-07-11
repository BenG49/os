#include "gdt.h"

static gdt_entry entries[ENTRIES];

static gdt_entry make_entry(
    uint32_t base,
    uint32_t limit,
    uint8_t access,
    uint8_t granularity)
{
    access |= PRESENT;
    granularity |= ((limit >> 16) & 0xf);
    
    return (gdt_entry) {
        (uint16_t)(limit & 0xffff),     // limit
        (uint16_t)(base & 0xffff),      // base_low
        (uint8_t)((base >> 16) & 0xff), // base_mid
        access,                         // access
        granularity,                    // granularity
        (uint8_t)((base >> 24) & 0xff)  // base_hi
    };
}

void init_gdt()
{
    entries[0] = make_entry(0, 0, 0, 0); // null entry
    // kernel code segment (0x8)
    entries[1] = make_entry(0, 0, READ_WRITE | EXECUTABLE | NONSYS_DESC, CODE_GRANULARITY);
    // kernel data segment (0x10)
    entries[2] = make_entry(0, 0, READ_WRITE | NONSYS_DESC | DIR, 0);

    // user code segment (0x1b)
    entries[3] = make_entry(0, 0, USER_PRIVL | READ_WRITE | EXECUTABLE | NONSYS_DESC, CODE_GRANULARITY);
    // user data segment (0x23)
    entries[4] = make_entry(0, 0, USER_PRIVL | READ_WRITE | NONSYS_DESC | DIR, 0);

    gdtr gdt_reg = {
        .size = (uint16_t)(sizeof(entries) - 1),
        .offset = (size_t)entries
    };

    load_gdt(&gdt_reg);

    puts("GDT loaded at ");
    put_uint((size_t)&gdt_reg, 16);
    newline();
}
