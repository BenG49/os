; https://forum.osdev.org/viewtopic.php?f=1&t=30739&sid=52089b032c69cf50c7113523702d3747&start=15
bits 64
global load_gdt

load_gdt:
	; pointer passed in rdi (x86_64 System V ABI)
	lgdt [rdi]

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	pop rax	; get caller location
	push 0x08
	push rax
	retfq	; far returns and sets cs to 0x08
