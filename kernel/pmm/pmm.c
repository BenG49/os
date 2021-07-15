#include "pmm.h"

static mem_block start_block = { .start = NULL };
static unsigned int sector_size_bits;
static unsigned int sector_size_bytes;

/*

|-------------------------------------------------------|
|     start of segment    |      mem_block struct       |
|-------------------------------------------------------|
| end of mem_block struct |          bitmap             |
|-------------------------------------------------------|
|      end of bitmap      | start of allocatable memory |
|-------------------------------------------------------|

*/

void init_pmm(struct stivale2_struct_tag_memmap *memmap, unsigned int sector_size)
{
    sector_size_bits = sector_size * 8;
    sector_size_bytes = sector_size;

    struct stivale2_mmap_entry *entries = (void *)memmap->memmap;
    struct stivale2_mmap_entry *entry;

    mem_block *cur = &start_block;

    for (size_t i = 0; i < memmap->entries; ++i)
    {
        entry = &entries[i];

        // if map entry isn't usable
        if ((entry->type != STIVALE2_MMAP_USABLE) &&
            (entry->type != STIVALE2_MMAP_ACPI_RECLAIMABLE) &&
            (entry->type != STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE))
            continue;
        
        // b = bitmap size, k = sector size, l = (length - mem block)
        // b + b(8k) = l
        // b(8k + 1) = l
        // b = l / (8k + 1)
        int bitmap_size = (entry->length - sizeof(mem_block)) / (8 * sector_size + 1);
        int header_size = sizeof(mem_block) + bitmap_size;

        void *entry_start  = (void *)entry->base;
        void *bitmap_start = entry_start + sizeof(mem_block);
        void *mem_start    = bitmap_start + bitmap_size;

        // BUG ADDRESS: 0x7fc6df40
        // VIRTUAL ADDR OF PAGE: 0xfd0c5230
        // error: write access
        // clears bitmap (all of memory is free)
        memset(bitmap_start, 0, bitmap_size);

        // first entry
        if (start_block.start == NULL)
        {
            start_block = (mem_block) {
                .start  = mem_start,
                .end    = (void *)(entry->base + entry->length),
                .len    = entry->length - header_size,
                .bitmap = bitmap_start,
                .bitmap_len = bitmap_size,
                .full   = false,
                .next   = NULL
            };
        }
        else
        {
            mem_block *b = (void *)entry->base;
            *b = (mem_block) {
                .start  = mem_start,
                .end    = (void *)(entry->base + entry->length),
                .bitmap = bitmap_start,
                .bitmap_len = bitmap_size,
                .full   = false,
                .next   = NULL
            };

            cur->next = b;
            cur = b;

            // FIXME: add page allocation so i dont just use the first two blocks
            break;
        }
    }

    puts("PMM initialized\n");
}

static bool bitmap_test(uint8_t *bitmap, int offset)
{
    uint8_t sector = bitmap[offset >> 3];
    uint8_t shift = (7 - (offset & 0b111));

    return ((sector >> shift) & 1) == 1;
}

static void bitmap_set(uint8_t *bitmap, int offset)
{
    bitmap[offset >> 3] |= ((0b10000000 >> (offset & 0b111)));
}

static void *offset_to_addr(void *bitmap, int offset)
{
    return bitmap + offset * sector_size_bytes;
}

void *malloc(size_t size)
{
    if (size < 1)
        return NULL;

    void *out;
    int out_offset = 0;
    int counter = 0;

    mem_block *cur = &start_block;

    // loops through memory blocks
    for (;;)
    {
        out = cur->bitmap;

        if (size > cur->len)
            goto END; // this ir probably bad idk

        // loop through each bit of bitmap
        for (int offset = 0; offset < cur->bitmap_len * 8; ++offset)
        {
            // sector is allocated
            if (bitmap_test(cur->bitmap, offset))
                counter = 0;
            // sector is free
            else
            {
                // puts("free sector ");
                if (counter == 0)
                {
                    // reset vars
                    out_offset = offset;
                    out = offset_to_addr(cur->bitmap, out_offset);
                }

                counter += sector_size_bytes;

                if (counter >= size)
                {
                    // number of sectors instead of bytes
                    int max = counter / sector_size_bytes;

                    // set the sec12 to allocated
                    for (int i = 0; i < max; ++i)
                        bitmap_set(cur->bitmap, out_offset + i);

                    return out;
                }
            }
        }

   END: if (cur->next == NULL)
            break;
        
        cur = cur->next;
    }

    return NULL;
}

void free(void *ptr) { }
