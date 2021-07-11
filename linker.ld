OUTPUT_FORMAT(elf64-x86-64)
ENTRY(kmain)

SECTIONS
{
    /* higher half kernel */
    . = 0xffffffff80200000;

    /* Make sure that the stivale header doesn't get discarded */
    .stivale2hdr : {
        KEEP(*(.stivale2hdr))
    }

    /* Then let's place all the other traditional executable sections afterwards. */
    .text : {
        *(.text*)
    }

    .rodata : {
        *(.rodata*)
    }

    .data : {
        *(.data*)
    }

    .bss : {
        *(COMMON)
        *(.bss*)
    }
}