#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdbool.h>

char *itoa(int i, char *buffer, int base);
char *reverse(char *buffer, int len);
int strcmp(const char *a, const char* b);

inline static size_t strlen(const char *str)
{
    size_t i = 0;

    while (*str++ != 0)
    {
        ++i;
    }

    return i;
}

#endif // STRING_H
