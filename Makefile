# $@ = target file
# $< = first dependency
# $^ = all dependencies

C_SOURCES=$(wildcard kernel/*.c kernel/drivers/*.c)
HEADERS=$(wildcard kernel/*.h kernel/drivers/*.h)
LD=$()
# replace .c with .o
OBJ=${C_SOURCES:.c=.o}

CC=/usr/local/i386elfgcc/bin/i386-elf-gcc
# GDB=/usr/local/i386elfgcc/bin/i386-elf-gdb
GDB=/usr/bin/gdb
LD=/usr/local/i386elfgcc/bin/i386-elf-ld

OUT_IMG=os-img.bin

$(OUT_IMG): boot/bootsect.bin kernel.bin
	cat $^ > $@

# KERNEL
kernel.bin: kernel/kernel_entry.o ${OBJ}
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debug
kernel.elf: kernel/kernel_entry.o ${OBJ}
	$(LD) -o $@ -Ttext 0x1000 $^

# Generic rules
%.o: %.c ${HEADERS}
	$(CC) -g $(CFLAGS) -ffreestanding -c $< -o $@

%.o: %.asm
	nasm -f elf $< -o $@

%.bin: %.asm
	nasm -f bin $< -o $@

run: $(OUT_IMG)
	qemu-system-i386 -machine q35 -fda $<

debug: $(OUT_IMG) kernel.elf
	qemu-system-i386 -machine q35 -S -gdb tcp::1234 -fda $(OUT_IMG) &

gdb:
	$(GDB) -ex "target remote localhost:1234" -ex "symbol-file kernel.elf" -ex "set disassembly-flavor intel" -ex "set architecture i8086" -ex "layout asm" -ex "layout regs"

clean:
	rm $(OBJ) kernel/kernel_entry.o boot/*.bin
	rm *.bin $(OUT_IMG) *.elf
