; http://www.jamesmolloy.co.uk/tutorial_html/5.-IRQs%20and%20the%20PIT.html
; in isr.c
[extern isr_handler]

; takes in IRQ
%macro IRQ 1
    global isr%1
isr%1:
    cli
    push byte 0
    push byte %1
    jmp irq_common_stub
%endmacro

%macro ERR_IRQ 1
    global isr%1
isr%1:
    cli
    ; error already pushed onto stack
    push byte %1
    jmp irq_common_stub
%endmacro

IRQ 0
IRQ 1
IRQ 2
IRQ 3
IRQ 4
IRQ 5
IRQ 6
IRQ 7
ERR_IRQ 8
IRQ 9
ERR_IRQ 10
ERR_IRQ 11
ERR_IRQ 12
ERR_IRQ 13
ERR_IRQ 14
IRQ 15
IRQ 16
IRQ 17
IRQ 18
IRQ 19
IRQ 20
IRQ 21
IRQ 22
IRQ 23
IRQ 24
IRQ 25
IRQ 26
IRQ 27
IRQ 28
IRQ 29
IRQ 30
IRQ 31

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

    ; call c handler
    cld
    call isr_handler

    pop ebx
    mov ds, bx
    mov ds, bx
    mov fs, bx
    mov gs, bx

    popa

    add esp, 8  ; "pops" null byte and isr num
    iret
