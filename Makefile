# $@ = target file
# $< = first dependency
# $^ = all dependencies
RAM_SIZE=4G
SERIAL=serial.log

C_SOURCES=$(shell find ./ -type f -name '*.c')
HEADERS=$(shell find ./ -type f -name '*.h')
OBJ=${C_SOURCES:.c=.o kernel/cpu/isr_wrapper.o}

CC=/usr/bin/gcc
GDB=/usr/bin/gdb
LD=/usr/bin/ld

OUT_IMG=os-img.bin
CFLAGS= -g -m32 -fno-builtin -fpic -fno-pie -fno-stack-protector	\
		-mno-red-zone -Wall -Werror -nostartfiles -nodefaultlibs
QFLAGS=	-machine q35									\
		-drive format=raw,if=floppy,file=$(OUT_IMG)		\
		-serial file:$(SERIAL)							\
		-no-reboot -no-shutdown							\
		-m $(RAM_SIZE)

.PHONY: run debug gdb clean

$(OUT_IMG): boot/bootsect.bin kernel.bin
	cat $^ > $@

# KERNEL
kernel.bin: kernel/kernel_entry.o ${OBJ}
	$(LD) -m elf_i386 -o $@ -T link.ld $^
#$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debug
kernel.elf: kernel/kernel_entry.o ${OBJ}
	$(LD) -melf_i386 -o $@ -Ttext 0x1000 $^

# Generic rules
%.o: %.c ${HEADERS}
	$(CC) $(CFLAGS) -ffreestanding -c $< -o $@

%.o: %.asm
	nasm -f elf $< -o $@

%.bin: %.asm
	nasm -f bin $< -o $@

%.s: %.c
	$(CC) $(CFLAGS) -S -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm -masm=intel -c $< -o $@

run: $(OUT_IMG)
	qemu-system-i386 $(QFLAGS)

debug: $(OUT_IMG) kernel.elf
	qemu-system-i386 -S -gdb tcp::1234 -d guest_errors,int $(QFLAGS) &
	$(GDB) -ex "target remote localhost:1234" -ex "symbol-file kernel.elf" -ex "set disassembly-flavor intel" -ex "set architecture i8086" -ex "layout asm" -ex "layout regs"

clean:
	rm kernel/kernel_entry.o boot/*.bin
	rm *.bin *.elf $(OBJ) 
