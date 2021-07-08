#include "string.h"

char *strcpy(char *dst, const char* src)
{
    char *out = dst;

    while (*src)
        *dst++ = *src++;

    return out;
}

char *strncpy(char *dst, const char *src, size_t n) {
    char *out = dst;

    while (n--)
        *dst++ = *src++;
    
    return out;
}

char *strcat(char *dst, const char *src)
{
    char *out = dst;

    // move dst to null terminator
    while (*dst)
        ++dst;
    
    while (*src)
        *dst++ = *src++;
    
    // add null terminator
    *dst = 0;

    return out;
}

char *strncat(char *dst, const char *src, size_t n)
{
    char *out = dst;

    // move dst to null terminator
    while (*dst)
        ++dst;
    
    while (n--)
        *dst++ = *src++;
    
    // add null terminator
    *dst = 0;

    return out;
}

int strcmp(const char *str1, const char *str2)
{
    int i = 0;
    while (str1[i] && str1[i] == str2[i])
        ++i;

    return str1[i] - str2[i];
}

int strncmp(const char *str1, const char *str2, size_t n)
{
    int i = 0;
    while (--n && str1[i] && str1[i] == str2[i])
    {
        ++i;
    }

    return str1[i] - str2[i];
}

size_t strlen(const char *str)
{
    size_t out = 0;

    while (*str++)
        ++out;
    
    return out;
}

char *reverse(char *str, size_t len)
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

char *uitoa(unsigned int n, char *buf, int base)
{
    if (base < 2 || base > 36)
    {
        *buf = 0;
        return buf;
    }

    if (n == 0)
    {
        buf = (base == 16) ? "0x0\0" : "0\0";
        return buf;
    }

    size_t i = 0;

    while (n > 0)
    {
        // 0x57 = ('a' - 10)
        if (base > 10 && n % base > 9)
            buf[i++] = n % base + 0x57;
        else
            buf[i++] = n % base + '0';
        
        n /= base;
    }

    if (base == 16)
    {
        buf[i++] = 'x';
        buf[i++] = '0';
    }

    buf[i] = 0;

    return reverse(buf, i);
}

char *itoa(int n, char *buf, int base)
{
    if (base < 2 || base > 36)
    {
        *buf = 0;
        return buf;
    }

    if (n == 0)
    {
        buf = (base == 16) ? "0x0\0" : "0\0";
        return buf;
    }

    size_t i = 0;
    bool sign = false;

    if (n < 0)
    {
        sign = true;
        n = -n;
    }

    while (n > 0)
    {
        // 0x57 = ('a' - 10)
        if (base > 10 && n % base > 9)
            buf[i++] = n % base + 0x57;
        else
            buf[i++] = n % base + '0';
        
        n /= base;
    }

    if (base == 16)
    {
        buf[i++] = 'x';
        buf[i++] = '0';
    }

    if (sign)
        buf[i++] = '-';

    buf[i] = 0;

    return reverse(buf, i);
}
