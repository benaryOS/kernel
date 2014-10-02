#include <constants.h>

extern void *pmm_alloc_block(void);
extern void page_map(struct page_context *,void *,void *,uint32_t);

extern size_t printk(const char *,...);

void *vmm_alloc_block(struct page_context *ctx)
{
	page_directory_t dir=ctx->directory;
	uint32_t i,j;
	for(i=0x100;i<0x400;i++)
	{
		page_table_t table=dir[i];
		if(!(((uint32_t)table)&PAGING_PRESENT))
		{
			for(j=1;j<0x400;j++)
			{
				uint32_t res=(i*0x400+j)*0x1000;
				void *ptr=pmm_alloc_block();
				page_map(ctx,(void *)res,ptr,PAGING_PRESENT|PAGING_WRITE|PAGING_USER);
				return (void *)res;
			}
		}
	}
	return 0;
}
