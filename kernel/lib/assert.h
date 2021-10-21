#ifndef ASSERT_H
#define ASSERT_H

#include "../drivers/tty.h"

static void __assert(const char *msg, const char *file, int line)
{
	printf("Assertion failed: %s at %s, line %d\n", msg, file, line);

	for (;;) asm volatile("hlt");
}

// glibc
#define assert(EXPR) (void)((EXPR) || (__assert (#EXPR, __FILE__, __LINE__),0))

#endif // ASSERT_H
