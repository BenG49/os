#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

#define true (1 == 1)
#define false (!true)

void _memcpy(uint16_t *src, uint16_t *dest, int bytes);
char *itoa(int i, char *buffer, int base);
char *reverse(char *buffer, int len);

#endif // UTIL_H
