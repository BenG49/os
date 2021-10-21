#include "pmm.h"

#include <boot/stivale2.h>

static mem_block *start_block = NULL;

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

static bool bitmap_test(uint8_t *bitmap, int idx)
{
	return (bitmap[idx >> 3] & (0b10000000 >> (idx & 0b111))) != 0;
}

static void bitmap_set(uint8_t *bitmap, int idx)
{
	bitmap[idx >> 3] |= (0b10000000 >> (idx & 0b111));
}

static void *align_up(void *addr, size_t align)
{
	return addr + (align - ((size_t)addr % align));
}

void print_pmm(struct stivale2_struct_tag_memmap *memmap)
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
		// printf("%s%x  \t(%x)\n", type_names[type], entry->base, entry->length);
	}

	putc('\n');
}

static bool usable_entry(uint32_t type)
{
	return type == STIVALE2_MMAP_USABLE
		// || type == STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE
		// || type == STIVALE2_MMAP_ACPI_RECLAIMABLE
	;
}

// FIXME:	assumes that usable entries are page aligned
//			assumes that total < PAGE_SIZE
static void *init_mem_hdr(struct stivale2_struct_tag_memmap *memmap)
{
	struct stivale2_mmap_entry *entries = (void *)memmap->memmap;
	size_t total = 0;

	// get bytes needed for hdr
	for (size_t i = 0; i < memmap->entries; ++i)
	{
		if (!usable_entry(entries[i].type))
			continue;

		// entries[i].length / PAGE_SIZE / 8;
		total += sizeof(mem_block) + (entries[i].length >> 15);
	}

	// place hdr
	for (size_t i = 0; i < memmap->entries; ++i)
	{
		if (!usable_entry(entries[i].type))
			continue;

		// found block that header can be placed in
		if (entries[i].length >= total)
		{
			void *out = entries[i].base;

			// header uses whole memory block, mark block as used
			if (entries[i].length <= PAGE_SIZE)
				entries[i].type = STIVALE2_MMAP_RESERVED;
			// otherwise, move block 1 page higher
			else
			{
				entries[i].base += PAGE_SIZE;
				entries[i].length -= PAGE_SIZE;
			}

			return out;
		}
	}
}

void init_pmm(struct stivale2_struct_tag_memmap *memmap)
{
	struct stivale2_mmap_entry *entries = (void *)memmap->memmap;

	// location to store information structs at (first usable page found)
	void *hdr_ptr = init_mem_hdr(memmap);

	mem_block *cur = start_block;

	for (size_t i = 0; i < memmap->entries; ++i)
	{
		if (!usable_entry(entries[i].type))
			continue;
		
		// entries[i].length / PAGE_SIZE
		size_t pages = entries[i].length >> 12;
		// pages / 8
		size_t bitmap_sz = sizeof(mem_block) + (pages >> 3);

		mem_block *new;

		if (start_block == NULL)
		{
			cur = hdr_ptr;
			start_block = hdr_ptr;
		}

		new = hdr_ptr;
		hdr_ptr += sizeof(mem_block);

		uint8_t *bitmap = hdr_ptr;
		hdr_ptr += bitmap_sz;

		new->addr	= entries[i].base;
		new->pages	= pages;
		new->bitmap = bitmap;
		new->bitmap_len = bitmap_sz;
		new->full   = false;
		new->next   = NULL;

		// continue linked list if not first block
		if (start_block != NULL)
		{
			cur->next = new;
			cur = new;
		}
	}

	cur = start_block;
	while (true)
	{
		puts("---- BITMAP LIST ENTRY ----");
		printf("ADDR: %x\tPAGES: %u\n", cur->addr, cur->pages);
		printf("BITMAP: %x\tLEN: %u\n", cur->bitmap, cur->bitmap_len);
		printf("FULL: %d\tNEXT: %x\n", cur->full, cur->next);
		puts("");

		if (cur->next)
			cur = cur->next;
		else
			break;
	}
}

void *page_alloc() { }
