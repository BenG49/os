#include "mem.h"

void *memcpy(void *dst, const void *src, size_t n)
{
	uint8_t *d = dst;
	const uint8_t *s = src;

	while (n--)
		*d++ = *s++;
		// d[n] = s[n];
	
	return dst;
}

void *memmove(void *dst, const void* src, size_t n)
{
	const char *s = src;
	char *d = dst;

	// buffer to save src
	char temp[n];

	for (int i = 0; i < n; ++i)
		temp[i] = s[i];
	
	for (int i = 0; i < n; ++i)
		d[i] = temp[i];

	// free(temp);
	return dst;
}



int memcmp(const void *ptr1, const void *ptr2, size_t n)
{
	int i = 0;
	const char *cptr1 = ptr1;
	const char *cptr2 = ptr2;

	// TODO: check if there's an off by one error
	while (--n && cptr1[i] == cptr2[i])
		++i;

	return cptr1[i] - cptr2[i];
}

void *memset(void *ptr, uint8_t value, size_t n)
{
	uint8_t *p = ptr;

	while (n--)
		*p++ = value;
	
	return ptr;
}
