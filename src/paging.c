#include <constants.h>

extern void *pmm_alloc_block(void);

static struct page_context *kernel_ctx;

void paging_context_activate(struct page_context *ctx)
{
	asm volatile("mov %0, %%cr3" : : "r" (&ctx->directory));
}

struct page_context *paging_context_create(void)
{
	struct page_context *ctx=pmm_alloc_block();

	int i;
	for(i=0;i<0x400;i++)
	{
		ctx->directory.page[i]=0;
	}

	return ctx;
}

void page_map(struct page_context *ctx,void *virt,void *phys)
{
	//TODO:map page
}

void paging_init(void)
{
	kernel_ctx=paging_context_create();

	paging_context_activate(kernel_ctx);

	uint32_t cr0;
	asm volatile("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= (1 << 31);
	asm volatile("mov %0, %%cr0" : : "r" (cr0));
}

