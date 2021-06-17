; http://www.jamesmolloy.co.uk/tutorial_html/5.-IRQs%20and%20the%20PIT.html
; in isr.c
[extern isr_handler]

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
    pusha

    mov ax, ds  ; save ds, segment descriptor
    push eax

    ; kernel segment
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp    ; pointer to base of registers on stack

    ; call c handler
    cld
    call isr_handler

    pop ebx     ; pop esp
    pop ebx     ; pop ds
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa

    add esp, 8  ; "pops" null byte and isr num
    iret
