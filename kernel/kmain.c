#include "kmain.h"

static char *type_names[] = {
    "",
    "USABLE:                 ",
    "RESERVED:               ",
    "ACPI RECLAIMABLE:       ",
    "ACPI NVS:               ",
    "BAD MEMORY:             ",
    "BOOTLOADER RECLAIMABLE: ",
    "KERNEL & MODULES:       ",
    "FRAMEBUFFER:            "
};

void print_mmap(struct stivale2_struct_tag_memmap *memmap)
{
    struct stivale2_mmap_entry *entries = (void *)memmap->memmap;
    struct stivale2_mmap_entry *entry;

    uint32_t type;

    printf("\n ----- MEMMAP: %u entries ----- \n", memmap->entries);

    for (int i = 0; i < memmap->entries; ++i)
    {
        entry = &entries[i];

        type = entry->type;
        if (type > 10)
            type -= 4090; // offset from 0x1000

        printf("%s%x  \t-> %x\n", type_names[type], entry->base, entry->base + entry->length);
    }

    putc('\n');
}

void kmain(struct stivale2_struct *tags)
{
    struct stivale2_struct_tag_framebuffer *framebuffer;
    framebuffer = get_tag(tags, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);

    struct stivale2_struct_tag_terminal *terminal;
    terminal = get_tag(tags, STIVALE2_STRUCT_TAG_TERMINAL_ID);

    struct stivale2_struct_tag_memmap *memmap;
    memmap = get_tag(tags, STIVALE2_STRUCT_TAG_MEMMAP_ID);

    if (framebuffer == NULL || terminal == NULL || memmap == NULL)
        for (;;) asm volatile("hlt");

    init_tty(framebuffer);
    init_idt();
    init_timer(1);
    init_keyboard();

    print_mmap(memmap);
    init_pmm(memmap, 1);

    disable_cursor();

    for (;;) asm volatile("hlt");
}
