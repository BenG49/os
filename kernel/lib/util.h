#ifndef UTIL_H
#define UTIL_H

#define BIT_TEST(byte, idx) ((byte) & (1 << (idx)))
#define BIT_SET(byte, idx) ((byte) |= (1 << (idx)))
#define BIT_CLEAR(byte, idx) ((byte) &= (~(1 << (idx))))

#endif // UTIL_H
