# $@ = target file
# $< = first dependency
# $^ = all dependencies
SERIAL=log/serial.log
QLOG  =log/qemu.log

C_SOURCES 	:= $(shell find ./kernel/ ./boot/ -type f -name '*.c')
#HEADERS=$(shell find . -type f -name '*.h')
ASM 		:= $(shell find ./kernel/ ./boot/ -type f -name '*.s')
OBJ 		:= ${ASM:.s=.o} ${C_SOURCES:.c=.o}

CC=/usr/bin/gcc
GDB=/usr/bin/gdb
LD=/usr/bin/ld

KERNEL = kernel.elf
ISO    = kernel.iso

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
	-fno-omit-frame-pointer	\
	-fno-lto				\
	-fno-pic -fPIE			\
	-mno-sse				\
	-mno-sse2				\
	-mno-mmx				\
	-mno-80387				\
	-mno-red-zone			\
	-Wall					\
	-pipe					\
	-O2

QFLAGS :=						\
	-serial file:$(SERIAL)		\
	-M q35						\
	-m 4G						\
	-no-reboot -no-shutdown		\
	-drive format=raw,media=cdrom,file=$(ISO)

XORRISO :=								\
	-as mkisofs -b limine-cd.bin		\
	-no-emul-boot						\
	-boot-load-size 4					\
	-boot-info-table					\
	--efi-boot limine-eltorito-efi.bin	\
	-efi-boot-part --efi-boot-image		\
	--protective-msdos-label			\
	iso_root -o $(ISO)					\

.PHONY: all run limine clean

all: $(ISO)

$(ISO): $(KERNEL)
	mkdir -p iso_root
	cp $(KERNEL) limine.cfg				\
		limine/limine.sys				\
		limine/limine-cd.bin			\
		limine/limine-eltorito-efi.bin	\
		iso_root/
	
	xorriso $(XORRISO)
	./limine/limine-install $(ISO)

	rm -rf iso_root

$(KERNEL): $(OBJ)
	$(CC) $(LINKFLAGS) $^ -o $@

# Generic rules
#%.o: %.c ${HEADERS}
%.o: %.c
	$(CC) $(CFLAGS) -g -c $< -o $@

%.o: %.s
	nasm -f elf64 $< -o $@

%.bin: %.s
	nasm -f bin $< -o $@

%.s: %.c
	$(CC) $(CFLAGS) -S -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm -masm=intel -c $< -o $@

run: $(ISO)
	qemu-system-x86_64 $(QFLAGS)

debug: $(ISO) $(KERNEL)
	qemu-system-x86_64 -S -gdb tcp::1234 -d guest_errors,int -D $(QLOG) $(QFLAGS) &
	$(GDB) -ex "target remote localhost:1234" -ex "symbol-file $(KERNEL)" -ex "set disassembly-flavor intel" -ex "set architecture i386:x86-64" -ex "layout asm" -ex "layout regs"

limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v2.0-branch-binary --depth=1
	make -C limine

clean:
	rm *.bin *.elf $(OBJ) $(ISO)
