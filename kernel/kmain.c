#include <kmain.h>
#include <lib/assert.h>

void kmain(struct stivale2_struct *tags)
{
	struct stivale2_struct_tag_framebuffer *buf = get_tag(tags, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
	struct stivale2_struct_tag_memmap *memmap   = get_tag(tags, STIVALE2_STRUCT_TAG_MEMMAP_ID);
	struct stivale2_struct_tag_epoch *epoch	 = get_tag(tags, STIVALE2_STRUCT_TAG_EPOCH_ID);

	assert(buf != NULL  && memmap != NULL && epoch != NULL);


	init_tty(buf);
	init_pmm(memmap);
	debug_ok("PMM initialized");

	printf("epoch: %u\n", epoch->epoch);

	print_pmm(memmap);

	// desc tables
	init_gdt();
	init_idt();

	// devices
	init_timer(1);
	init_keyboard();

	for (;;) asm volatile("hlt");
}
