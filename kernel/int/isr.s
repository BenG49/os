bits 64

extern isr_handler

%macro isr 1
    global isr%1
isr%1:
    push 0
    push %1
    jmp isr_common_stub
%endmacro

%macro err_isr 1
    global isr%1
isr%1:
    push %1
    jmp isr_common_stub
%endmacro

; exceptions
isr     0
isr     1
isr     2
isr     3
isr     4
isr     5
isr     6
isr     7
err_isr 8
isr     9
err_isr 10
err_isr 11
err_isr 12
err_isr 13
err_isr 14
isr     15
isr     16
err_isr 17
isr     18
isr     19
isr     20
isr     21
isr     22
isr     23
isr     24
isr     25
isr     26
isr     27
isr     28
isr     29
err_isr 30
isr     31

; vector offset is 32
isr     32
isr     33
isr     34
isr     35
isr     36
isr     37
isr     38
isr     39
err_isr 40
isr     41
err_isr 42
err_isr 43
err_isr 44
err_isr 45
err_isr 46
isr     47

isr_common_stub:
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

    ; pass stack pointer as arg to isr_handler
    mov rdi, rsp

    ; call C handler
    cld
    call isr_handler

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax

    ; "pops" error byte and isr number
    add rsp, 16
    ; iret pops the interrupt data from the stack
    iretq
