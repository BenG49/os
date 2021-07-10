; https://forum.osdev.org/viewtopic.php?f=1&t=30739&sid=52089b032c69cf50c7113523702d3747&start=15
bits 64
default rel

[global gdt_asm]

gdt_asm:
    ; pointer passed in rdi (x86_64 System V ABI)
    ; lgdt [rdi]

    lea rax, [rel .clear] ; gets around the relocation linking error

    ; push 8
    ; push rax
    ; retf    ; jumps to clear and sets cs to 0x08 because it's a far jump

.clear:
    mov rax, 0x10
    mov ds, rax
    mov es, rax
    mov fs, rax
    mov gs, rax
    mov ss, rax

    ret
