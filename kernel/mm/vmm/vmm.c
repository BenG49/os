#include "vmm.h"

#include <mm/pmm/pmm.h>
#include <drivers/tty.h>

#define LEVELS 4

#define PT_BITS 9
#define OFFSET_BITS 12

#define L1_OFFSET (OFFSET_BITS)
#define L2_OFFSET (L1_OFFSET + PT_BITS)
#define L3_OFFSET (L2_OFFSET + PT_BITS)
#define L4_OFFSET (L3_OFFSET + PT_BITS)

#define PAGE_SIZE 0x1000
#define PT_SIZE ((uint64_t)1 << PT_BITS)

// 15 bits are sign extension
#define HIGHER_HALF ((uint64_t)0xFFFF800000000000)
// 111111111111111 11000
// L4 is 2 bits

// flags
#define PRESENT   ((uint64_t)1 << 0)
#define WRITABLE  ((uint64_t)1 << 1)
#define SYS       ((uint64_t)1 << 2)
#define WRITE_THR ((uint64_t)1 << 3)
#define NO_CACHE  ((uint64_t)1 << 4)
#define ACCESSED  ((uint64_t)1 << 5)
#define DIRTY     ((uint64_t)1 << 6)
#define HUGEPG    ((uint64_t)1 << 7)
#define GLOBAL    ((uint64_t)1 << 8)
#define NOEXEC    ((uint64_t)1 << 63)

#define ADDR_MASK 0xFFFFFFFFFFFFF000
#define PT_IDX_MASK 0x1FF

static page_entry_t *top_level;

static inline uint64_t pt_to_addr(int idx, int lvl)
{
	return idx << (lvl * PT_BITS + OFFSET_BITS);
}

void *next_lvl(page_entry_t *table, int idx)
{
	idx &= PT_IDX_MASK;

	// page is present
	if (table[idx] & PRESENT)
		return (uint64_t *)(table[idx] & ADDR_MASK);
	else
	{
		uint64_t *new_table = page_alloc();
		// write address
		table[idx] = (uint64_t)new_table | PRESENT | WRITABLE | SYS;
		return new_table;
	}
}

void map_page(uint64_t virt, uint64_t phys, uint64_t flags)
{
	// remove offset
	phys &= ADDR_MASK;

	printf("mapping %x to %x\n", virt, phys);
	printf("mapping %d %d %d %d\n", (virt >> L4_OFFSET) & PT_IDX_MASK
	, (virt >> L3_OFFSET) & PT_IDX_MASK
	, (virt >> L2_OFFSET) & PT_IDX_MASK
	, (virt >> L1_OFFSET) & PT_IDX_MASK);

	uint64_t *l3 = next_lvl(top_level, virt >> L4_OFFSET);
	uint64_t *l2 = next_lvl(l3, virt >> L3_OFFSET);
	uint64_t *l1 = next_lvl(l2, virt >> L2_OFFSET);
	l1[(virt >> L1_OFFSET) & PT_IDX_MASK] = phys | flags;
}

void print_mappings(page_entry_t *table, int lvl, uint64_t virt)
{
	for (int i = 0; i < PT_SIZE; ++i)
	{
		if (!(table[i] & PRESENT))
			continue;

		// recursively call
		if (lvl != 0)
			print_mappings(table[i] & ADDR_MASK, lvl - 1, virt |= pt_to_addr(i, lvl));
		else
			printf("%x -> %x\n", virt | (i << OFFSET_BITS), table[i] & ADDR_MASK);
	}
}

void init_vmm()
{
	// per stivale2
	// 0x0 - 4 GiB -> 0xffff800000000000

	top_level = page_alloc();

	// 1 GiB = 1 << 30
	// 1 GiB of pages = 1 << 18

	uint64_t phys = 0;
	map_page(phys + HIGHER_HALF, phys, PRESENT | WRITABLE | SYS);
	// for (int i = 0; i < 1 << 18; ++i, phys += PAGE_SIZE)
	// 	map_page(phys + HIGHER_HALF, phys, PRESENT | WRITABLE | SYS);
	
	print_mappings(top_level, 3, 0);

	// asm("mov %0, %%cr3" ::"dN"(top_level));
}
