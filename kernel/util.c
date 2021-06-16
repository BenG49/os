#include "util.h"

void _memcpy(uint16_t *src, uint16_t *dest, int bytes)
{
    for (int i = 0; i < bytes; ++i)
        dest[i] = src[i];
}

char *reverse(char *str, int len)
{
    int begin = 0;
    int end = len - 1;
    char temp;

    while (begin < end)
    {
        temp = str[begin];
        str[begin++] = str[end];
        str[end--] = temp;
    }

    return str;
}

char *itoa(int n, char *str, int base)
{
    if (base < 2 || base > 36)
    {
        *str = '\0';
        return str;
    }

    if (n == 0)
    {
        if (base == 16)
        {
            str[0] = '0';
            str[1] = 'x';
            str[2] = '0';
            str += 3;
        } else
            *str++ = '0';

        *str = '\0';

        return str;
    }

    int i = 0;
    int sign = false;

    if (n < 0)
    {
        sign = true;
        n = -n;
    }

    while (n > 0)
    {
        // 0x57 is 'a' - 10
        if (base > 10 && n % base > 9)
            str[i++] = n % base + 0x57;
        else
            str[i++] = '0' + n % base;

        n /= base;
    }

    if (sign)
        str[i++] = '-';
    
    if (base == 16)
    {
        str[i++] = 'x';
        str[i++] = '0';
    }
    
    str[i] = '\0';

    return reverse(str, i);
}

size_t inline strlen(const char *str)
{
    size_t i = 0;

    while (*str++ != 0)
    {
        ++i;
    }

    return i;
}
