#include "stivale_util.h"

void *get_tag(struct stivale2_struct *stivale2_struct, uint64_t id_request)
{
	// traverse through linked list
	// address pointed to by current list value
	struct stivale2_tag *current_tag = (void *)stivale2_struct->tags;

	while (1)
	{
		if (current_tag == NULL)
			return NULL;
		
		if (current_tag->identifier == id_request)
			return current_tag;
		
		current_tag = (void *)current_tag->next;
	}
}
