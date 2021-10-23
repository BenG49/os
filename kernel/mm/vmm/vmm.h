#ifndef VMM_H
#define VMM_H

// TODO: support 5 level paging

#include <stdint.h>
#include <stddef.h>

typedef uint64_t page_entry_t;

// get next level address and if nonexistent, malloc it
void *next_lvl(page_entry_t *table, int index);
void map_page(uint64_t virt, uint64_t phys, uint64_t flags);

void init_vmm();

#endif // VMM_H
