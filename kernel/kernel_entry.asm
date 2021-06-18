[bits 32]
[extern kernel_main]   ; external C function
call kernel_main       ; call C function
jmp $