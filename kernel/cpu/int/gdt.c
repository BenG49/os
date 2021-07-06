#include "gdt.h"

static gdt_entry gdt;
static gdt_desc desc;

void init_gdt()
{
    gdt.base_low = 0;
    gdt.base_mid = 0;
    gdt.base_high = 0;

    gdt.limit_low = 0;
}
