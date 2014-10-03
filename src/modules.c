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

extern void *memcpy(void *,void *,size_t);

extern struct task *task_create_kernel(void *);
extern void task_add(struct task *);

void elf_load(void *,size_t);

void modules_init(struct multiboot *mb)
{
	if(mb->mbs_mods_count!=1)
	{
		return;
	}
	struct mb_module *modules=mb->mbs_mods_addr;
	size_t i;
	for(i=0;i<mb->mbs_mods_count;i++)
	{
		elf_load(modules[i].start,modules[i].end-modules[i].start);
	}
}
