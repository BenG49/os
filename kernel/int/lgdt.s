; https://forum.osdev.org/viewtopic.php?f=1&t=30739&sid=52089b032c69cf50c7113523702d3747&start=15
bits 64

[global lgdt]

lgdt:
    ; pointer passed in rdi (x86_64 System V ABI)
    ; lgdt [rdi]
    pop rax
    lgdt [rax]

    mov rax, 0x10
    mov ds, rax
    mov es, rax
    mov fs, rax
    mov gs, rax
    mov ss, rax

    pop rax     ; get caller location

    push 0x08
    push rax
    retfq       ; far returns and sets cs to 0x08
