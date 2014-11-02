/*
 * Copyright 2014 benaryorg (benaryorg@benaryos.org)
 *
 * This file is part of benaryOS.
 *
 * benaryOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * benaryOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with benaryOS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <constants.h>

static uint32_t bitmap[PMM_BITMAP_SIZE]={};

extern const void KERNEL_START,KERNEL_END;

void pmm_free(void *addr)
{
	uint32_t a=(uint32_t)addr;
	a/=0x1000;
	bitmap[a/0x20]|=1<<(a%0x20);
}

void pmm_use(void *addr)
{
	uint32_t a=(uint32_t)addr;
	a/=0x1000;
	bitmap[a/0x20]&=~(1<<(a%0x20));
}

void *pmm_alloc_block(void)
{
	size_t i,j;
	for(i=0;i<PMM_BITMAP_SIZE;i++)
	{
		if(bitmap[i])
		{
			for(j=0;j<0x20;j++)
			{
				if((bitmap[i])&(0x01<<j))
				{
					void *addr=(void *)((i*0x20+j)*0x1000);
					pmm_use(addr);
					return addr;
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
			char *s=(char *)((uint32_t)mmap->base);
			char *e=s+mmap->length;
			while(s<e)
			{
				pmm_free(s);
				s+=0x1000;
			}
		}
		mmap++;
	}
	char *addr;

	for(addr=(char *)&KERNEL_START;addr<(char *)&KERNEL_END;addr+=0x1000)
	{
		pmm_use((void *)addr);
	}
}
