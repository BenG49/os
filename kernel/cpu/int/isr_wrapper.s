; in isr.c
extern isr_handler

; takes in IRQ
%macro IRQ 2
    global isr%1
isr%1:
    cli
    push byte 0
    push byte %2
    jmp irq_common_stub
%endmacro

%macro ERR_IRQ 2
    global isr%1
isr%1:
    cli
    ; error already pushed onto stack
    push byte %2
    jmp irq_common_stub
%endmacro

; exceptions (basically the same but function is named exc)
%macro EXC 1
    global exc%1
exc%1:
    cli
    push byte 0
    push byte %1
    jmp irq_common_stub
%endmacro

%macro ERR_EXC 1
    global exc%1
exc%1:
    cli
    ; error already pushed onto stack
    push byte %1
    jmp irq_common_stub
%endmacro

; EXCEPTIONS
EXC 0
EXC 1
EXC 2
EXC 3
EXC 4
EXC 5
EXC 6
EXC 7
ERR_EXC 8
EXC 9
ERR_EXC 10
ERR_EXC 11
ERR_EXC 12
ERR_EXC 13
ERR_EXC 14
EXC 15
EXC 16
ERR_EXC 17
EXC 18

; vector offset is 32 and 40 (32-47)
IRQ     0, 32
IRQ     1, 33
IRQ     2, 34
IRQ     3, 35
IRQ     4, 36
IRQ     5, 37
IRQ     6, 38
IRQ     7, 39
ERR_IRQ 8, 40
IRQ     9, 41
ERR_IRQ 10, 42
ERR_IRQ 11, 43
ERR_IRQ 12, 44
ERR_IRQ 13, 45
ERR_IRQ 14, 46
IRQ     15, 47

irq_common_stub:
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    mov rdi, rsp

    ; call C handler
    cld
    call isr_handler

    push r15
    push r14
    push r13
    push r12
    push r11
    push r10
    push r9
    push r8
    push rsi
    push rdi
    push rbp
    push rdx
    push rcx
    push rbx
    push rax

    add rsp, 16 ; "pops" null byte and isr num
    iretq
