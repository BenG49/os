#include "util.h"

void _memcpy(u16 *src, u16 *dest, int bytes)
{
    for (int i = 0; i < bytes; ++i)
        dest[i] = src[i];
}
