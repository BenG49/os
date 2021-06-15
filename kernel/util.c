#include "util.h"

void _memcpy(uint16_t *src, uint16_t *dest, int bytes)
{
    for (int i = 0; i < bytes; ++i)
        dest[i] = src[i];
}
