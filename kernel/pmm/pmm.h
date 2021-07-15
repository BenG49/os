#ifndef PMM_H
#define PMM_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "../lib/mem.h"
#include "../drivers/tty.h"
#include "../../boot/stivale2.h"

// memory area header
typedef struct {
    void *start;
    void *end;
    size_t len;

    uint8_t *bitmap;
    size_t bitmap_len;

    bool full;

    void *next;
} mem_block;

// sector size in bytes
void init_pmm(struct stivale2_struct_tag_memmap *memmap, unsigned int sector_size);

void *malloc(size_t size);
void free(void *ptr);

#endif // PMM_H
