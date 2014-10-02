#include <constants.h>

extern void *pmm_alloc_block(void);

extern size_t printk(const char *,...);

static struct page_context *kernel_ctx;

void paging_context_activate(struct page_context *ctx)
{
	asm volatile("mov %0, %%cr3" : : "r" (ctx->directory));
}

void page_map(struct page_context *ctx,void *virtp,void *physp,uint32_t flags)
{
	uint32_t virt=(uint32_t)virtp;
	uint32_t phys=(uint32_t)physp;

	if(((virt|phys)&0xfff)||!virt)
	{
		printk("bad pointers\n");
		return;
	}

	uint32_t pdoff=(virt>>22)%0x1000;
	uint32_t ptoff=(virt>>12)%0x1000;

	uint32_t i;

	page_directory_t dir=ctx->directory;

	i=(uint32_t)dir[pdoff];
	if(!(i&PAGING_PRESENT))
	{
		i=(uint32_t)pmm_alloc_block();
		i|=PAGING_PRESENT|PAGING_WRITE;
		dir[pdoff]=(page_table_t)i;
	}
	page_table_t table=(page_table_t)(i&(~0xfff));

	i=(uint32_t)table[ptoff];
	if(i&PAGING_PRESENT)
	{
		printk("page already mapped\n");
		return;
	}
	page_t page=(page_t)(phys|(flags&0xfff));
	table[ptoff]=page;

	asm volatile("invlpg %0" : : "m" (*(char *)virtp));
}

void page_map_kernel(struct page_context *ctx)
{
	//FIXME: this is not (only) the kernel
	size_t i;
	for(i=0x1000;i<0x400000;i+=0x1000)
	{
		page_map(ctx,(void *)i,(void *)i,PAGING_PRESENT|PAGING_USER);
	}
}

void paging_context_create(struct page_context *ctx)
{
	int i;
	ctx->directory=pmm_alloc_block();
	for(i=0;i<0x400;i++)
	{
		ctx->directory[i]=0;
	}
	page_map(ctx,(void *)ctx,(void *)ctx,PAGING_PRESENT|PAGING_WRITE);
	page_map(ctx,(void *)ctx->directory,(void *)ctx->directory,PAGING_PRESENT|PAGING_WRITE);
	page_map_kernel(ctx);
}

void paging_init(void)
{
	kernel_ctx=pmm_alloc_block();
	paging_context_create(kernel_ctx);
	paging_context_activate(kernel_ctx);
	//kernel_ctx=(void *)VMM_PAGEDIR;

	uint32_t cr0;
	asm volatile("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= (1 << 31);
	asm volatile("mov %0, %%cr0" : : "r" (cr0));
}

