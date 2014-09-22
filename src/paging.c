#include <constants.h>

extern void *pmm_alloc_block(void);

extern size_t printk(const char *,...);

static struct page_context *kernel_ctx;

void paging_context_activate(struct page_context *ctx)
{
	asm volatile("mov %0, %%cr3" : : "r" (ctx->directory));
}

struct page_context *paging_context_create(void)
{
	struct page_context *ctx=pmm_alloc_block();
	ctx->directory=(page_directory_t)pmm_alloc_block();

	int i;
	for(i=0;i<0x400;i++)
	{
		ctx->directory[i]=0;
	}

	return ctx;
}

void page_map(struct page_context *ctx,void *virtp,void *physp,uint32_t flags)
{
	uint32_t virt=(uint32_t)virtp;
	uint32_t phys=(uint32_t)physp;

	if((virt|phys)&0xfff)
	{
		printk("bad flags\n");
		return;
	}

	uint32_t pdoff=(virt>>22)%0x1000;
	uint32_t ptoff=(virt>>12)%0x1000;

	uint32_t i;

	page_directory_t dir=ctx->directory;

	i=(uint32_t)dir[pdoff];
	if(!(i&PAGING_PT_PRESENT))
	{
		i=(uint32_t)pmm_alloc_block();
		i|=PAGING_PT_PRESENT|PAGING_PT_WRITE;
		dir[pdoff]=(page_table_t)i;
	}
	page_table_t table=(page_table_t)(i&(~0xfff));

	i=(uint32_t)table[ptoff];
	if(i&PAGING_PT_PRESENT)
	{
		printk("page already mapped\n");
		return;
	}
	page_t page=(page_t)(phys|(flags&0xfff));
	table[ptoff]=page;

	asm volatile("invlpg %0" : : "m" (*(char *)virtp));
}

void paging_init(void)
{
	kernel_ctx=paging_context_create();

	int i;
	for(i=0;i<0x4000000;i+=0x1000)
	{
		page_map(kernel_ctx,(void *)i,(void *)i,PAGING_PT_PRESENT|PAGING_PT_WRITE);
	}
	paging_context_activate(kernel_ctx);

	uint32_t cr0;
	asm volatile("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= (1 << 31);
	asm volatile("mov %0, %%cr0" : : "r" (cr0));
}

