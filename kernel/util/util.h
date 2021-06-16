#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

inline static void _memcpy(uint16_t *src, uint16_t *dest, int bytes)
{
    for (int i = 0; i < bytes; ++i)
        dest[i] = src[i];
}

inline static void memset(void *addr, uint8_t val, size_t n)
{
    uint8_t *a = addr;

    while (n-- > 0)
        *a++ = val;
}

inline static size_t strlen(const char *str)
{
    size_t i = 0;

    while (*str++ != 0)
    {
        ++i;
    }

    return i;
}

inline static bool bit_test(uint8_t flag, int bitpos)
{
    return ((flag >> bitpos) & 1) == 1;
}

inline static uint8_t set_bit(uint8_t flag, int bitpos)
{
    return flag | (1UL << bitpos);
}

inline static uint8_t clear_bit(uint8_t flag, int bitpos)
{
    return flag & ~(1UL << bitpos);
}

#define asm __asm__ volatile

#define cli() asm ("cli")
#define sti() asm ("sti")

#define MAX(a, b) (((a) < (b)) ? (a) : (b))
#define MIN(a, b) (((a) > (b)) ? (a) : (b))

#endif // UTIL_H
