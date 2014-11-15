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

extern void *pmm_alloc_block(void);
extern void page_map(struct page_context *,void *,void *,uint32_t);

extern void *page_map_tmp(void *);
extern void page_unmap_tmp(void);

extern void *paging_unflag(void *);

void *vmm_alloc_block(struct page_context *ctx,int user)
{
	page_directory_t dir=page_map_tmp(ctx?ctx->directory:(void *)PAGEDIR);
	uint32_t i,j;
	for(i=0x100;i<0x400;i++)
	{
		if((uint32_t)dir[i]&PAGING_PRESENT)
		{
			page_table_t table=page_map_tmp(paging_unflag(dir[i]));
			for(j=1;j<0x400;j++)
			{
				if(!(table[i]&PAGING_PRESENT))
				{
					uint32_t res=(i*0x400+j)*0x1000;
					void *ptr=pmm_alloc_block();
					page_map(ctx,(void *)res,ptr,PAGING_PRESENT|PAGING_WRITE|(user?PAGING_USER:0));
					return (void *)res;
				}
			}
		}
	}
	return 0;
}

void *vmm_alloc_block_user(struct page_context *ctx)
{
	return vmm_alloc_block(ctx,1);
}

void *vmm_alloc_block_kernel(struct page_context *ctx)
{
	return vmm_alloc_block(ctx,0);
}
