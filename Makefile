# $@ = target file
# $< = first dependency
# $^ = all dependencies
RAM_SIZE=4G
SERIAL=log/serial.log
QLOG=log/qemu.log

C_SOURCES=$(shell find ./kernel/ -type f -name '*.c')
HEADERS=$(shell find ./kernel/ -type f -name '*.h')
ASM=$(shell find ./kernel/ -type f -name '*.asm')
OBJ := $(filter-out ./kernel/kernel_entry.o, ${ASM:.asm=.o} ${C_SOURCES:.c=.o})

CC=/usr/bin/gcc
GDB=/usr/bin/gdb
LD=/usr/bin/ld

OUT_IMG=os-img.bin
CFLAGS= -m32 -fno-builtin -fpic -fno-pie -fno-stack-protector	\
		-mno-red-zone -Wall -Werror -nostartfiles -nodefaultlibs -ffreestanding
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

# Used for debug
kernel.elf: kernel/kernel_entry.o ${OBJ}
	$(LD) -melf_i386 -o $@ -Ttext 0x1000 $^

# Generic rules
%.o: %.c ${HEADERS}
	$(CC) $(CFLAGS) -g -c $< -o $@

%.o: %.asm
	nasm -f elf $< -o $@

%.bin: %.asm
	nasm -f bin $< -o $@

%.s: %.c
	$(CC) $(CFLAGS) -S -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm -masm=intel -c $< -o $@

run: $(OUT_IMG)
	qemu-system-i386 $(QFLAGS)

debug: $(OUT_IMG) kernel.elf
	qemu-system-i386 -S -gdb tcp::1234 -d guest_errors,int -D $(QLOG) $(QFLAGS) &
	$(GDB) -ex "target remote localhost:1234" -ex "symbol-file kernel.elf" -ex "set disassembly-flavor intel" -ex "set architecture i8086" -ex "layout asm" -ex "layout regs"

clean:
	rm kernel/kernel_entry.o boot/*.bin
	rm *.bin *.elf $(OBJ) 
