# $@ = target file
# $< = first dependency
# $^ = all dependencies

C_SOURCES=$(wildcard kernel/*.c kernel/drivers/*.c kernel/cpu/*.c kernel/util/*.c)
HEADERS=$(wildcard kernel/*.h kernel/drivers/*.h kernel/cpu/*.h kernel/util/*.h)
OBJ=${C_SOURCES:.c=.o kernel/cpu/isr_wrapper.o}

# CC=/usr/local/i386elfgcc/bin/i386-elf-gcc
CC=/usr/bin/gcc
# GDB=/usr/local/i386elfgcc/bin/i386-elf-gdb
GDB=/usr/bin/gdb
# LD=/usr/local/i386elfgcc/bin/i386-elf-ld
LD=/usr/bin/ld

OUT_IMG=os-img.bin
CFLAGS= -g -m32 -fno-builtin -fpic -fno-pie -fno-stack-protector -mno-red-zone -Wall -Werror

.PHONY: run debug gdb clean

$(OUT_IMG): boot/bootsect.bin kernel.bin
	cat $^ > $@

# KERNEL
kernel.bin: kernel/kernel_entry.o ${OBJ}
	$(LD) -m elf_i386 -o $@ -T link.ld $^
#$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debug
kernel.elf: kernel/kernel_entry.o ${OBJ}
	$(LD) -m elf_i386 -o $@ -Ttext 0x1000 $^

# Generic rules
%.o: %.c ${HEADERS}
	$(CC) $(CFLAGS) -ffreestanding -c $< -o $@

%.o: %.asm
	nasm -f elf $< -o $@

%.bin: %.asm
	nasm -f bin $< -o $@

%.s: %.c
	$(CC) $(CFLAGS) -S -fno-stack-protector -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm -masm=intel -ffreestanding -c $< -o $@

run: $(OUT_IMG)
	qemu-system-i386 -machine q35 -fda $<

debug: $(OUT_IMG) kernel.elf
	qemu-system-i386 -machine q35 -S -gdb tcp::1234 -d guest_errors,int -fda $(OUT_IMG) &

gdb:
	$(GDB) -ex "target remote localhost:1234" -ex "symbol-file kernel.elf" -ex "set disassembly-flavor intel" -ex "set architecture i8086" -ex "layout asm" -ex "layout regs"

clean:
	rm kernel/kernel_entry.o boot/*.bin
	rm *.bin *.elf $(OBJ) 
