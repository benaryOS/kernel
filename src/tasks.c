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
extern uint32_t pid_get(void);
extern void *vmm_alloc_block_kernel(struct page_context *);
extern void *virt_to_phys(struct page_context *,void *);
extern void *page_map_tmp(void *);
extern void page_unmap_tmp(void);

void task_create_cpu(struct cpu_state *dst,void *entry)
{
	struct cpu_state cpu=
	{
		.eax=0,
		.ebx=0,
		.ecx=0,
		.edx=0,
		.esi=0,
		.edi=0,
		.ebp=0,
		.esp=0,
		.eip=(uint32_t)entry,
		.cs=0,
		.ss=0,
		.eflags=0x202,
	};
	*dst=cpu;
}

struct task *task_create_kernel(struct page_context *ctx,void *entry)
{
	char *stack=(char *)vmm_alloc_block_kernel(ctx);
	char *stack_mapped=page_map_tmp(virt_to_phys(ctx,stack));
	struct cpu_state *state=(struct cpu_state *)(stack_mapped+4096-sizeof(struct cpu_state));
	task_create_cpu(state,entry);
	state->cs=0x08;
	page_unmap_tmp();
	struct task *task=(struct task *)vmm_alloc_block_kernel(ctx);
	struct task *task_mapped=page_map_tmp(virt_to_phys(ctx,task));
	task_mapped->cpu=state;
	task_mapped->pid=pid_get();
	page_unmap_tmp();
	return task;
}

struct task *task_create_user(struct page_context *ctx,void *entry)
{
	char *stack=(char *)vmm_alloc_block_kernel(ctx);
	char *stack_mapped=page_map_tmp(virt_to_phys(ctx,stack));
	struct cpu_state *state=(struct cpu_state *)(stack_mapped+4096-sizeof(struct cpu_state));
	task_create_cpu(state,entry);
	state->cs=0x18|0x03;
	state->ss=0x20|0x03;
	state->esp=(uint32_t)(((char *)vmm_alloc_block_user(ctx))+4096);
	page_unmap_tmp();
	struct task *task=(struct task *)vmm_alloc_block_kernel(ctx);
	struct task *task_mapped=page_map_tmp(virt_to_phys(ctx,task));
	task_mapped->cpu=state;
	task_mapped->pid=pid_get();
	page_unmap_tmp();
	return task;
}

