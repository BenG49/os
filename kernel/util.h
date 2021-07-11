#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

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
