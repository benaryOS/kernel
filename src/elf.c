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

extern size_t printk(const char *,...);
extern void *memcpy(void *,void *,size_t);

extern struct task *task_create_kernel(void *);
extern void task_add(struct task *);

void elf_load(void *elf,size_t length)
{
	void *end=((char *)elf)+length;

	struct elf_header *header=(struct elf_header *)elf;
	//FIXME: if(header->magic!=ELF_MAGIC) does not work on some systems
	if(0)
	{
		printk("broken elf magic\n");
		return;
	}
	struct elf_header_program *pheader=(struct elf_header_program *)(((char *)elf)+header->ph_offset);
	//TODO:create a task
	//TODO:use the tasks page_context
	size_t i,j;
	//FIXME:i not used
	for(i=0;i<header->ph_entry_count;i++)
	{
		void *dst=(void *)pheader->virt_addr;
		void *src=(void *)(((char *)elf)+pheader->offset);
		//TODO: copy without pagefault
		if(pheader->type==1)
		{
			for(j=0;j<pheader->mem_size;j++)
			{
				((char *)dst)[j]=0;
			}
			//FIXME:place this somewhere useful
			if(pheader->file_size+((char *)src)>(char *)end)
			{
				printk("corrupt elf\n");
			}
			memcpy(dst,src,pheader->file_size);
		}
	}
	//TODO:create the task with the context
	struct task *t=task_create_kernel((void *)header->entry);
	//FIXME:maybe we should return the task * to create the context outside this function
	//FIXME:so we can reuse this function to build userspace processes later
	task_add(t);
}
