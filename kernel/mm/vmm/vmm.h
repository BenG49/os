#ifndef VMM_H
#define VMM_H

#include <stdint.h>
#include <stddef.h>

#define PAGE_SIZE 0x1000

typedef struct page_table {
	
} __attribute__((aligned(PAGE_SIZE))) page_table;

#endif // VMM_H
