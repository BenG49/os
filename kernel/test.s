; https://forum.osdev.org/viewtopic.php?f=1&t=30739&sid=52089b032c69cf50c7113523702d3747&start=15
bits 64
default rel

[global func]

func:
    lea rax, [rel .flush]

    push 0x28
    ; push 0x08
    push rax
    retfq       ; far jump to .flush

.flush:
    mov rax, 0x30
    ; mov rax, 0x10
    mov ds, rax
    mov es, rax
    mov fs, rax
    mov gs, rax
    mov ss, rax

    ret
