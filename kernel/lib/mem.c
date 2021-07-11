#include "mem.h"

void *memcpy(void *dest, const void *src, size_t bytes)
{
    char *csrc = (char *)src;
    char *cdest = (char *)dest;

    for (int i = 0; i < bytes; ++i)
        cdest[i] = csrc[i];
    
    return dest;
}

void *memset(void *ptr, int val, size_t num)
{
    char *a = (char *)ptr;

    while (num-- > 0)
        *a++ = val;
    
    return ptr;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
    int i = 0;
    char *cptr1 = (char *)ptr1;
    char *cptr2 = (char *)ptr2;

    while (cptr1[i] == cptr2[i])
    {
        ++i;
    }

    return cptr1[i] - cptr2[i];
}

void *memmove(void *dest, const void* src, size_t bytes)
{
    char *csrc = (char *)src;
    char *cdest = (char *)dest;

    // buffer to save src
    char temp[bytes];

    for (int i = 0; i < bytes; ++i)
        temp[i] = csrc[i];
    
    for (int i = 0; i < bytes; ++i)
        cdest[i] = temp[i];

    // free(temp);
    return dest;
}
