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
extern void *vmm_alloc_block(struct page_context *);

extern size_t printk(const char *,...);

static struct page_context *kernel_ctx;

static int active=0;

void paging_context_activate(struct page_context *ctx)
{
	//now start using the pagedirectory in the virtual memory (@VMM_PAGEDIR)
	ctx->directory=(page_directory_t)VMM_PAGEDIR;
	asm volatile("mov %0, %%cr3" : : "r" (ctx->phys));
}

void page_map(struct page_context *ctx,void *virtp,void *physp,uint32_t flags)
{
	//convert to uint32_t for shifting
	uint32_t virt=(uint32_t)virtp;
	uint32_t phys=(uint32_t)physp;

	//check if someone wants to add flags in the address or wants to map 0
	if(((virt|phys)&0xfff)||!virt)
	{
		printk("bad pointers\n");
		return;
	}

	//offset in the page directory
	uint32_t pdoff=(virt>>22)%0x1000;
	//offset in the page table
	uint32_t ptoff=(virt>>12)%0x1000;

	uint32_t i;

	//get the directory
	page_directory_t dir=ctx->directory;

	//temporary var
	i=(uint32_t)dir[pdoff];
	//if the pagetable is not present
	if(!(i&PAGING_PRESENT))
	{
		//allocate a new one
		i=(uint32_t)pmm_alloc_block();
		i|=PAGING_PRESENT|PAGING_WRITE;
		dir[pdoff]=(page_table_t)i;
	}
	//TODO: we are accessing physical memory
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
		//FIXME: no user rights
		page_map(ctx,(void *)i,(void *)i,PAGING_PRESENT|PAGING_USER);
	}
	//map the pagedirectory to this virtual address
	page_map(ctx,(void *)VMM_PAGEDIR,ctx->directory,PAGING_PRESENT);
}

void paging_context_create(struct page_context *ctx)
{
	int i;
	ctx->directory=ctx->phys=pmm_alloc_block();
	for(i=0;i<0x400;i++)
	{
		ctx->directory[i]=0;
	}
	page_map(ctx,ctx,ctx,PAGING_PRESENT|PAGING_WRITE);
	page_map(ctx,(void *)VMM_PAGEDIR,ctx->directory,PAGING_PRESENT|PAGING_WRITE);
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

	active=1;
}

