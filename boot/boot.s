; https://raw.githubusercontent.com/stivale/stivale/master/stivale2.h
section .stivale2hdr
    dq 0                ; entry_point - overrides ELF entry point if not zero
    dq stack            ; stack
    dq (1 << 1)         ; pointers are offset to higher half
    dq framebuffer_tag  ; tags pointer

tags:
terminal_tag:
.tag:
    ; STIVALE2_HEADER_TAG_TERMINAL_ID
    dq 0xa85d499b1823be72
    dq 0    ; pointer to next (end of linked list)

    dq 0    ; unused flags

framebuffer_tag:
.tag:
    ; STIVALE2_HEADER_TAG_FRAMEBUFFER_ID 
    dq 0x3ecc1bc43d0f7971
    dq terminal_tag

    dw 0    ; all set to 0
    dw 0    ; bootloader picks values
    dw 0

section .bss

resb 0x1000

stack: