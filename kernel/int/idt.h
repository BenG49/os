#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include <lib/mem.h>
#include <cpu/sys.h>
#include <cpu/ports.h>
#include <drivers/tty.h>

#define INT_COUNT 0x100
#define PIC_OFFSET 0x20

#define ISR(n) extern void isr##n();

// exceptions
ISR(0)
ISR(1)
ISR(2)
ISR(3)
ISR(4)
ISR(5)
ISR(6)
ISR(7)
ISR(8)
ISR(9)
ISR(10)
ISR(11)
ISR(12)
ISR(13)
ISR(14)
ISR(15)
ISR(16)
ISR(17)
ISR(18)
ISR(19)
ISR(20)
ISR(21)
ISR(22)
ISR(23)
ISR(24)
ISR(25)
ISR(26)
ISR(27)
ISR(28)
ISR(29)
ISR(30)
ISR(31)

// hardware interrupts
ISR(32)
ISR(33)
ISR(34)
ISR(35)
ISR(36)
ISR(37)
ISR(38)
ISR(39)
ISR(40)
ISR(41)
ISR(42)
ISR(43)
ISR(44)
ISR(45)
ISR(46)
ISR(47)

typedef struct {
	uint16_t offset_low;
	uint16_t selector;   // code segment in GDT or LDT
	uint8_t ist;
	uint8_t flags;
	uint16_t offset_mid;
	uint32_t offset_hi;
	uint32_t zero;
} __attribute__((packed)) idt_entry;

typedef struct {
	uint16_t size;
	uint64_t offset;
} __attribute__((packed)) idtr;

typedef struct {
	regs regs;
	uint64_t isr_num;
	uint64_t err_code;
	uint64_t rip;
	uint64_t cs;
	uint64_t rflags;
	uint64_t rsp;
	uint64_t ss;
} __attribute__((packed)) stack;

typedef void (*handler)(const stack *);

void init_idt();

// called by isr_common_stub in isr.s with info about interrupt on stack
void isr_handler(const stack *regs);
void set_handler(uint8_t isr, handler h);

#endif // IDT_H
