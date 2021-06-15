[bits 32]
[extern kernel_main]   ; external C function
call kernel_main       ; call c function
jmp $