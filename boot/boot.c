#include <stdint.h>
#include <stddef.h>
#include "stivale2.h"

static uint8_t stack[1024];

/*
terminal header tag:
    
*/
static struct stivale2_header_tag_terminal terminal_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
        .next = 0
    },
    .flags = 0
};

struct stivale2_header header = {
    .entry_point = 0,   // if not zero, overrides elf entry point as entry point
    .stack = (uintptr_t)stack + sizeof(stack),  // x86 stacks grow downwards
    .flags = (1 << 1),  // first bit = all pointers offset to higher
    .tags
};
