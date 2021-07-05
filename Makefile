# $@ = target file
# $< = first dependency
# $^ = all dependencies
SERIAL=log/serial.log
QLOG=log/qemu.log

C_SOURCES=$(shell find ./kernel/ -type f -name '*.c')
HEADERS=$(shell find ./kernel/ -type f -name '*.h')
ASM=$(shell find . -type f -name '*.s')
OBJ := $(filter-out ./kernel/kernel_entry.o, ${ASM:.s=.o} ${C_SOURCES:.c=.o})

CC=/usr/bin/gcc
GDB=/usr/bin/gdb
LD=/usr/bin/ld

KERNEL := kernel.elf
ISO    := kernel.iso

LINKFLAGS :=				\
	-fno-pic -fPIE			\
	-Wl,-static,-pie,--no-dynamic-linker,-ztext	\
	-static-pie				\
	-nostdlib				\
	-T link.ld				\
	-z max-page-size=0x1000
CFLAGS :=					\
	-I.						\
	-ffreestanding			\
	-fno-stack-protector	\
	-fno-pic -fPIE			\
	-mno-80387				\
	-mno-red-zone			\
	-Wall -Wextra			\
	-O2

QFLAGS :=						\
	-serial file:$(SERIAL)		\
	-no-reboot -no-shutdown		\
	-drive format=raw,media=cdrom,file=$(ISO)

XORRISO :=								\
	-as mkisofs -b limine-cd.bin	\
	-no-emul-boot						\
	-boot-load-size 4					\
	-boot-info-table					\
	--efi-boot limine-eltorito-efi.bin	\
	-efi-boot-part --efi-boot-image		\
	--protective-msdos-label			\
	iso_root -o $(ISO)					\

.PHONY: all run init_limine clean

all: $(ISO)

$(ISO): $(KERNEL)
	mkdir -p iso_root
	cp -v $(KERNEL) limine.cfg limine/limine.sys	\
		limine/limine-cd.bin			\
		limine/limine-eltorito-efi.bin	\
		iso_root/
	
	xorriso $(XORRISO)
	./limine/limine-install $(ISO)

	rm -rf iso_root

$(KERNEL): $(OBJ)
	$(CC) $(LINKFLAGS) $^ -o $@

# Generic rules
%.o: %.c ${HEADERS}
	$(CC) $(CFLAGS) -g -c $< -o $@

%.o: %.s
	nasm -f elf64 $< -o $@

%.bin: %.s
	nasm -f bin $< -o $@

%.s: %.c
	$(CC) $(CFLAGS) -S -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm -masm=intel -c $< -o $@

run: $(OUT_IMG)
	qemu-system-x86_64 $(QFLAGS)

# debug: $(OUT_IMG) kernel.elf
# 	qemu-system-i386 -S -gdb tcp::1234 -d guest_errors,int -D $(QLOG) $(QFLAGS) &
# 	$(GDB) -ex "target remote localhost:1234" -ex "symbol-file kernel.elf" -ex "set disassembly-flavor intel" -ex "set architecture i8086" -ex "layout asm" -ex "layout regs"

init-limine:
# download limine binaries
	git clone https://github.com/limine-bootloader/limine.git --branch=v2.0-branch-binary --depth=1
# make limine
	make -C limine

clean:
	rm *.bin *.elf $(OBJ) $(ISO)
	rm -r iso_root
