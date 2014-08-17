#include <constants.h>

static uint32_t bitmap[PMM_BITMAP_SIZE]={};

void pmm_free(void *addr)
{
	uint32_t a=(uint32_t)addr;
	a/=4096;
	bitmap[a/32]|=1<<(a%32);
}

void pmm_use(void *addr)
{
	uint32_t a=(uint32_t)addr;
	a/=4096;
	bitmap[a/32]&=~(1<<(a%32));
}

void *pmm_alloc_block(void)
{
	size_t i,j;
	for(i=0;i<PMM_BITMAP_SIZE;i++)
	{
		if(bitmap[i])
		{
			for(j=0;j<32;j++)
			{
				if((bitmap[i]>>j)&0x01)
				{
					return (void *)((i*32+j)*4096);
				}
			}
		}
	}
	return 0;
}

void pmm_init(struct multiboot *mb)
{
	struct multiboot_mmap *mmap=mb->mbs_mmap_addr;
	struct multiboot_mmap *mmap_end=(struct multiboot_mmap *)(((int *)mmap)+mb->mbs_mmap_length);
	while(mmap<mmap_end)
	{
		if(mmap->type==1)
		{
			int *s=(int *)((uint32_t)mmap->base);
			int *e=s+mmap->length;
			while(s<e)
			{
				pmm_free(s);
				s+=0x1000;
			}
		}
		mmap++;
	}
}
