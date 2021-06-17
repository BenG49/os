#ifndef STRING_H
#define STRING_H

#include <stdbool.h>

char *itoa(int i, char *buffer, int base);
char *reverse(char *buffer, int len);
bool streq(char *a, char* b);

#endif // STRING_H
