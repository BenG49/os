#ifndef PMM_H
#define PMM_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <lib/mem.h>
#include <drivers/tty.h>
#include <boot/stivale2.h>

#define PAGE_SIZE 0x1000
#define OFFSET_BITS 12

// memory area header
typedef struct mem_block {
	void *addr;
	size_t pages;

	uint8_t *bitmap;
	size_t bitmap_len;

	bool full;

	struct mem_block *next;
} mem_block;

/**
 * Creates internal memory map linked list, with each area of
 * reclaimable/usable memory assigned a bitmap signifying if
 * its ages are allocated
 */
void init_pmm(struct stivale2_struct_tag_memmap *memmap);
void print_pmm(struct stivale2_struct_tag_memmap *memmap);

void *page_alloc();

#endif // PMM_H
