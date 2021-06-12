; in protected mode, the segment register becomes an index to a
; segment descriptor (SD) in the GDT

; GDT has following information:
;   base address (32 bits), start of segment in physical mem
;   segment limit (20 bits), size of segment
;   flags
; https://wiki.osdev.org/Global_Descriptor_Table
gdt_start:
    dq 0            ; null 8 zero bytes

gdt_code:
    dw 0xffff       ; limit 0:15
    dw 0            ; base address 0:15
    db 0            ; base address 23:16
    db 10011010b    ; access byte
    db 11001111b    ; flags (4 bits) + limit 16:19
    db 0            ; base address 24:31

gdt_data:
    dw 0xffff       ; limit 0:15
    dw 0            ; base address 0:15
    db 0            ; base address 23:16
    db 10010010b    ; access byte (slightly changed)
    db 11001111b    ; flags (4 bits) + limit 16:19
    db 0            ; base address 24:31

gdt_end:
    dw gdt_end - gdt_start - 1  ; size of GDT - 1
    dd gdt_start                ; address of GDT as double word (4 bytes)

; offsets of segments from gdt start
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
