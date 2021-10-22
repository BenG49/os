#include "pmm.h"

#include <boot/stivale2.h>
#include <lib/assert.h>
#include <lib/util.h>

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
	}

	putc('\n');
}

static void print_alloc()
{
	mem_block *cur = start_block;

	puts("---- PAGE ALLOCATIONS ----");

	while (true)
	{
		printf("%x: ", cur->addr);

		for (int i = 0; i < cur->bitmap_len; ++i)
		{
			if (cur->bitmap[i] == 0xff)
				continue;

			// loop over bits
			for (int j = 0; j < 8; ++j)
				if (BIT_TEST(cur->bitmap[i], j))
					printf("%x ", cur->addr + (((i << 3) + j) << OFFSET_BITS));
		}

		putc('\n');

		if (!cur->next)
			break;

		cur = cur->next;
	}
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
// TODO: consolidate blocks that are adjacent and usable (does not happen now bc only one usable type)
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
		total += sizeof(mem_block) + ((entries[i].length >> OFFSET_BITS) >> 3);
	}

	// place hdr
	for (size_t i = 0; i < memmap->entries; ++i)
	{
		if (!usable_entry(entries[i].type))
			continue;

		// found block that header can be placed in
		if (entries[i].length >= total)
		{
			void *out = (void *)entries[i].base;

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

	puts("ERROR: Failed to alloc page frame allocator header");
	assert(1);
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
		size_t pages = entries[i].length >> OFFSET_BITS;
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

		new->addr	= (void *)entries[i].base;
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

	/*cur = start_block;
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
	}*/

	print_alloc();
}

void *page_alloc()
{
	mem_block *cur = start_block;

	while (true)
	{
		if (!cur->full)
		{
			for (int i = 0; i < cur->bitmap_len; ++i)
			{
				// skip over filled entries
				if (cur->bitmap[i] == 0xff)
					continue;

				// loop over bits
				for (int j = 0; j < 8; ++j)
					// found empty page
					if (!BIT_TEST(cur->bitmap[i], j))
					{
						// i is units of 8, (i * 8) + j is in pages
						int addr_offset = ((i << 3) + j) << OFFSET_BITS;

						BIT_SET(cur->bitmap[i], j);

						print_alloc();

						return cur->addr + addr_offset;
					}
			}

			// very end of bitmap, all full
			cur->full = true;
		}

		if (!cur->next)
		{
			puts("ERROR: Failed to alloc page: OUT OF MEMORY");
			assert(1);
		}

		cur = cur->next;
	}
}
