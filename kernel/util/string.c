#include "string.h"

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
        str = (base == 16)?"0x0\0":"0\0";
        return str;
    }

    int i = 0;
    bool sign = false;

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

int strcmp(const char *a, const char *b)
{
    int i = 0;
    while (a[i] && a[i] == b[i])
    {
        ++i;
    }

    return a[i] - b[i];
}