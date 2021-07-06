#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdbool.h>

// copy string from src to dst
char *strcpy(char *dst, const char* src);

// copy first n characters from src to dst
char *strncpy(char *dst, const char *src, size_t n);

// appends src to dst
char *strcat(char *dst, const char *src);

// append first n characters from src to dst
char *strncat(char *dst, const char *src, size_t n);

// int strcoll(const char *str1, const char *str2);

// compares two strings
int strcmp(const char *str1, const char *str2);

// strcmp but first n chars
int strncmp(const char *str1, const char *str2, size_t n);

size_t strlen(const char *str);

char *reverse(char *str, size_t len);


// string conversions
char *itoa(int n, char *buf, int base);

#endif // STRING_H
