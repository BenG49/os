[bits 16]
; given vars: dh as sectors to read, dl drive, es:bx buffer addr
read_sectors:
    pusha
    push dx

    mov ah, 0x02
    mov al, dh      ; sector count
    mov ch, 0x0     ; cylinder
    mov cl, 0x02    ; for some reason sectors start counting at 1
    mov dh, 0x0     ; head number
    int 0x13

    jc error        ; if carry flag set, error

    pop dx          ; initial sector count

    cmp al, dh
    jne sector_count_error

    popa
    ret

error:
    mov bx, errormsg
    call print
    jmp hang

sector_count_error:
    mov bx, sectorerrormsg
    call print

    mov ah, 0x0e
    add ax, '0'
    int 0x10

hang:
    jmp $

errormsg: db 'Error loading sectors', 0
sectorerrormsg: db 'Error: loaded sectors ', 0
