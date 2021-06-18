#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stddef.h>

void *memcpy(void *dest, const void *src, size_t bytes);
void *memset(void *ptr, int val, size_t num);
int memcmp(const void *ptr1, const void *ptr2, size_t num);
void *memmove(void *dest, const void* src, size_t bytes);
// void *malloc(size_t size);

#endif // MEM_H