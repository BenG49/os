#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

#define true (1 == 1)
#define false (!true)

void _memcpy(uint16_t *src, uint16_t *dest, int bytes);

#endif // UTIL_H
