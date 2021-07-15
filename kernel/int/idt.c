#include "idt.h"

static idt_entry entries[INT_COUNT];
static handler handlers[INT_COUNT];

char *messages[32] = {
    "#DE Division by zero exception",
    "#DB Debug exception",
    "Non maskable interrupt",
    "#BP Breakpoint exception",
    "#OF Into detected overflow",
    "#BR Out of bounds exception",
    "#UD Invalid opcode exception",
    "#NM No coprocessor exception",
    "#DF Double fault",
    "Coprocessor segment overrun",
    "#TS Bad TSS",
    "#NP Segment not present",
    "#SS Stack fault",
    "#GP General protection fault",
    "#PF Page fault",
    "Exception (15)",
    "#MF x86 FP Exception",
    "#AC Alignment check exception",
    "#MC Machine check exception",
    "#XM Floating Point Exception",
    "#VE Virtualization Exception",
    "Exception (21)",
    "Exception (22)",
    "Exception (23)",
    "Exception (24)",
    "Exception (25)",
    "Exception (26)",
    "Exception (27)",
    "Exception (28)",
    "Exception (29)",
    "#SX Security Exception",
    "Exception (31)"
};

static void set_entry(uint8_t n, size_t handler_addr)
{
    entries[n].offset_low = (uint16_t)handler_addr;
    entries[n].offset_mid = (uint16_t)(handler_addr >> 16);
    entries[n].offset_hi  = (uint32_t)(handler_addr >> 32);

    // 0x28 = index 5 in GDT, or 64-bit code selector (stivale spec)
    entries[n].selector = 0x28;

    // unused
    entries[n].ist = 0;

    // gate type = 32 bit int, privilige lvl 0
    entries[n].flags = 0b10001110;

    entries[n].zero = 0;
}

// moves PIC interrupts to after CPU defined interrupts
// IBM did an oops and made exceptions and interrupts interfere in protected mode
static void pic_init()
{
    // init
    outb(PIC1_CMD, 0x11);
    outb(PIC2_CMD, 0x11);

    // set new offsets
    outb(PIC1_DATA, PIC_OFFSET);
    outb(PIC2_DATA, PIC_OFFSET + 8);

    outb(PIC1_DATA, 4);
    outb(PIC2_DATA, 2);

    outb(PIC1_DATA, 1);
    outb(PIC2_DATA, 1);

    pic_clear_masks();
}

void init_idt()
{
    // clear table
    memset(&entries, 0, sizeof(idt_entry) * INT_COUNT);

    // set pic vector offset
    pic_init();

    set_entry(0,  (size_t)isr0);
    set_entry(1,  (size_t)isr1);
    set_entry(2,  (size_t)isr2);
    set_entry(3,  (size_t)isr3);
    set_entry(4,  (size_t)isr4);
    set_entry(5,  (size_t)isr5);
    set_entry(6,  (size_t)isr6);
    set_entry(7,  (size_t)isr7);
    set_entry(8,  (size_t)isr8);
    set_entry(9,  (size_t)isr9);
    set_entry(10, (size_t)isr10);
    set_entry(11, (size_t)isr11);
    set_entry(12, (size_t)isr12);
    set_entry(13, (size_t)isr13);
    set_entry(14, (size_t)isr14);
    set_entry(15, (size_t)isr15);
    set_entry(16, (size_t)isr16);
    set_entry(17, (size_t)isr17);
    set_entry(18, (size_t)isr18);
    set_entry(19, (size_t)isr19);
    set_entry(20, (size_t)isr20);
    set_entry(21, (size_t)isr21);
    set_entry(22, (size_t)isr22);
    set_entry(23, (size_t)isr23);
    set_entry(24, (size_t)isr24);
    set_entry(25, (size_t)isr25);
    set_entry(26, (size_t)isr26);
    set_entry(27, (size_t)isr27);
    set_entry(28, (size_t)isr28);
    set_entry(29, (size_t)isr29);
    set_entry(30, (size_t)isr30);
    set_entry(31, (size_t)isr31);

    // hardware interrupts
    set_entry(32, (size_t)isr32);
    set_entry(33, (size_t)isr33);
    set_entry(34, (size_t)isr34);
    set_entry(35, (size_t)isr35);
    set_entry(36, (size_t)isr36);
    set_entry(37, (size_t)isr37);
    set_entry(38, (size_t)isr38);
    set_entry(39, (size_t)isr39);
    set_entry(40, (size_t)isr40);
    set_entry(41, (size_t)isr41);
    set_entry(42, (size_t)isr42);
    set_entry(43, (size_t)isr43);
    set_entry(44, (size_t)isr44);
    set_entry(45, (size_t)isr45);
    set_entry(46, (size_t)isr46);
    set_entry(47, (size_t)isr47);

    idtr idt = {
        sizeof(entries) - 1, // size
        (size_t)entries      // offset
    };

    asm volatile("lidtq %0" :: "m"(idt) : "memory");

    printf("IDT loaded at %x\n", idt.offset);

    // for some reason interrupt bit was cleared
    asm volatile("sti");
}

void isr_handler(const stack *regs)
{
    if (regs->isr_num < 32)
    {
        printf("%s: %x\n", messages[regs->isr_num], regs->err_code);

        // exception
        for (;;) { asm volatile("hlt"); }
    }

    // tell pic to end interrupt
    pic_eoi(regs->isr_num - PIC_OFFSET);

    // call interrupt/exception
    if (handlers[regs->isr_num] != NULL)
        handlers[regs->isr_num](regs);
    else
        printf("No ISR handler for ISR %u!\n", regs->isr_num);
}

void set_handler(uint8_t isr, handler h) { handlers[isr] = h; }
