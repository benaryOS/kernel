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

extern size_t printk(const char *,...);

extern void tss_entry_set(uint32_t,uint32_t);

extern void halt(void);

static struct task *current_task=0;
static struct task *first_task=0;

void task_add(struct task *t)
{
	if(first_task)
	{
		t->next=first_task->next;
		first_task->next=t;
	}
	else
	{
		t->next=t;
		first_task=t;
	}
}

struct cpu_state *schedule(struct cpu_state *cpu)
{
	if(current_task)
	{
		current_task->cpu=cpu;
		current_task=current_task->next;
		//printk("switching to %d\n",current_task->pid);
		cpu=current_task->cpu;
	}
	else
	{
		if(first_task)
		{
			current_task=first_task;
			cpu=current_task->cpu;
			//printk("starting first task\n");
		}
		else
		{
			printk("no tasks\n");
			halt();
		}
	}
	tss_entry_set(1,(uint32_t)cpu);
	return cpu;
}
