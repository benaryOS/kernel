#include <constants.h>

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
