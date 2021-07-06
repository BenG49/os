#include <stdint.h>
#include "stivale2.h"

static uint8_t stack[1024];

/*
terminal header tag:
    makes it so that limine will set up a terminal
*/
static struct stivale2_header_tag_terminal terminal_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
        .next = 0   // end of linked list, null ptr
    },
    // terminal has no flags
    .flags = 0
};

static struct stivale2_header_tag_framebuffer framebuffer_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = (uint64_t)&terminal_hdr_tag     // linked list, links to next tag
    },
    // if all values set to 0, bootloader picks values
    .framebuffer_width  = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp    = 0
};

// attribute directive tells compiler to put this in stivale2hdr section
__attribute__((section(".stivale2hdr"), used))
static struct stivale2_header header = {
    .entry_point = 0,                           // if not zero, overrides elf entry point as entry point
    .stack = (uintptr_t)stack + sizeof(stack),  // x86 stacks grow downwards
    .flags = (1 << 1),                          // first bit = all pointers offset to higher
    .tags = (uint64_t)&framebuffer_hdr_tag      // start of tags linked list
};
