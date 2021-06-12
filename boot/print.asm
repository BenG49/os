[bits 32]

VGA_MEM equ 0xb8000
COLOR equ 0x0f

; address to string is ebx
print_vga:
    pusha
    mov ecx, VGA_MEM    ; addr pointer

vga_loop:
    mov al, [ebx]
    cmp al, 0
    je vga_exit
    mov ah, COLOR

    ; ah:al has char:color data
    mov [ecx], ax

    add ecx, 2      ; move to next char
    inc ebx         ; move to next char
    jmp vga_loop

vga_exit:
    popa
    ret

[bits 16]

; given address in bx
print:
    pusha

print_loop:
    mov al, [bx]

    cmp al, 0
    je exit

    mov ah, 0x0e
    int 0x10

    inc bx
    jmp print_loop

newline:
    pusha

    mov al, 0xa
    mov ah, 0x0e    ; newline
    int 0x10
    mov al, 0x0d    ; carriage return
    int 0x10

exit:
    popa
    ret
