#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <stddef.h>

#define true (1 == 1)
#define false (!true)

char *itoa(int i, char *buffer, int base);
char *reverse(char *buffer, int len);

static void inline _memcpy(uint16_t *src, uint16_t *dest, int bytes)
{
    for (int i = 0; i < bytes; ++i)
        dest[i] = src[i];
}

static void inline memset(void *addr, uint8_t val, size_t n)
{
    uint8_t *a = addr;

    while (n-- > 0)
        *a++ = val;
}

static size_t inline strlen(const char *str)
{
    size_t i = 0;

    while (*str++ != 0)
    {
        ++i;
    }

    return i;
}

#define asm __asm__ volatile

#define cli() asm ("cli")
#define sti() asm ("sti")

#define MAX(a, b) (((a) < (b)) ? (a) : (b))
#define MIN(a, b) (((a) > (b)) ? (a) : (b))

#endif // UTIL_H
