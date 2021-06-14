#ifndef UTIL_H
#define UTIL_H

// from jdh tetris os
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long i64;

#define true (1 == 1)
#define false (!true)

void _memcpy(u16 *src, u16 *dest, int bytes);
void itoa(int val, char str[]);

#endif // UTIL_H
