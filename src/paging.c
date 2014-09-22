#include <constants.h>

static struct page_context kernel_ctx;

void paging_context_activate(struct page_context *ctx)
{
	asm volatile("mov %0, %%cr3" : : "r" (&ctx->directory));
}

void paging_init(void)
{
	paging_context_activate(&kernel_ctx);

	uint32_t cr0;
	asm volatile("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= (1 << 31);
	asm volatile("mov %0, %%cr0" : : "r" (cr0));
}
