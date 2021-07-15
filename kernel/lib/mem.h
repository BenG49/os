#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stddef.h>

// copy n bytes from src to dst
void *memcpy(void *dst, const void *src, size_t n);

// copy n bytes from src to dest - src and dest can overlap
void *memmove(void *dst, const void* src, size_t n);

// compares two blocks of memory
int memcmp(const void *ptr1, const void *ptr2, size_t n);

// fill n bytes at ptr with value
void *memset(void *ptr, uint8_t value, size_t n);

#endif // MEM_H
