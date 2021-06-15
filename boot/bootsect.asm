[org 0x7c00]
[bits 16]
    mov [BOOT_DRIVE], dl    ; save the drive that the BIOS places in dl
    ; init stack
    mov bp, 0x7c00
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print
    call newline

    ; set video mode to 80x25
    mov ah, 0
    mov al, 3
    int 0x10

    call kernel
    call loadpm

%include "boot/gdt.asm"
%include "boot/print.asm"
%include "boot/disk.asm"

kernel:
    mov bx, MSG_KERNEL
    call print
    call newline

    mov bx, 0x1000          ; buffer addr
    mov dh, 4               ; 2 sectors
    mov dl, [BOOT_DRIVE]    ; load drive from memory
    call read_sectors
    ret

loadpm:
    cli             ; clear interrupt flag
    lgdt [gdt_end]  ; load GDT

    mov eax, cr0
    or eax, 1
    mov cr0, eax    ; set Protected Environment flag cr0

    jmp 0x8:initpm

[bits 32]
initpm:
    mov bx, MSG_PROT_MODE
    call print_vga

    ; update segment registers
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; update 32 bit stack registers
    mov ebp, 0x90000
    mov esp, ebp

    sti                 ; set interrupt flag

    call KERNEL_ADDR    ; jump to kernel

MSG_REAL_MODE db "Booted in 16 bit real mode", 0
MSG_PROT_MODE db "Switched to 32 bit protected mode", 0
MSG_KERNEL    db "Loading kernel", 0

BOOT_DRIVE equ 0
KERNEL_ADDR equ 0x1000

; Magic number
times 510 - ($-$$) db 0
dw 0xaa55
