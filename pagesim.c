#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*

4 level paging

*/

// TODO: hugepages

#define PT_BITS 9
#define OFFSET_BITS 12
#define PT_SIZE 0x200
#define PAGE_SIZE 0x1000

#define ADDR_MASK ((uint64_t)0xFFFFFFFFFFFFF000)
#define OFFSET_MASK ((uint64_t)0xFFF)

#define PT_IDX(addr, lvl) (((addr) >> (lvl * (PT_BITS) + (OFFSET_BITS))) & (OFFSET_MASK))

#define PRESENT 	((uint64_t)(1 << 0))
#define WRITABLE 	((uint64_t)(1 << 1))
#define USER 		((uint64_t)(1 << 2))
#define NOEXEC 		((uint64_t)(1 << 63))

// get next level address and if nonexistent, malloc it
uint64_t *next_lvl(uint64_t *table, size_t idx)
{
	// page is present
	if (table[idx] & PRESENT)
		return (uint64_t *)(table[idx] & ADDR_MASK);
	else
	{
		uint64_t *new_table = aligned_alloc(PAGE_SIZE, PAGE_SIZE);
		// write address
		table[idx] = (uint64_t)new_table | PRESENT | WRITABLE | USER;
		return new_table;
	}
}

uint64_t v_to_phys(uint64_t addr, uint64_t cr3)
{
	uint64_t *l3 = next_lvl(cr3, PT_IDX(addr, 3));
	uint64_t *l2 = next_lvl(l3, PT_IDX(addr, 2));
	uint64_t *l1 = next_lvl(l2, PT_IDX(addr, 1));
	return (uint64_t)next_lvl(l1, PT_IDX(addr, 0));
}

void map_page(uint64_t virt, uint64_t phys, uint64_t flags, uint64_t cr3)
{
	// align to page size
	phys &= ~(OFFSET_MASK);

	uint64_t *l3 = next_lvl(cr3, PT_IDX(virt, 3));
	uint64_t *l2 = next_lvl(l3, PT_IDX(virt, 2));
	uint64_t *l1 = next_lvl(l2, PT_IDX(virt, 1));
	l1[PT_IDX(virt, 0)] = phys | flags;
}

int main()
{

}
