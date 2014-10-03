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

extern int printk(const char *,...);
extern void outb(uint16_t,uint8_t);

extern struct cpu_state *int_exception_handler(struct cpu_state *);
extern struct cpu_state *int_irq_handler(struct cpu_state *);
extern struct cpu_state *int_syscall_handler(struct cpu_state *);

struct cpu_state *int_unknown_handler(struct cpu_state *cpu)
{
	printk("interrupt(%d)\n",cpu->intr);
	return cpu;
}

struct cpu_state *int_handler(struct cpu_state *cpu)
{
	int intr=cpu->intr;
	struct cpu_state *(*f)(struct cpu_state *)=0;
	if(intr>=0x00&&intr<0x20)
	{
		f=int_exception_handler;
	}
	if(intr>=0x20&&intr<0x30)
	{
		f=int_irq_handler;
	}
	if(intr==0x30)
	{
		f=int_syscall_handler;
	}
	if(!f)
	{
		f=int_unknown_handler;
	}

	cpu=f(cpu);

	//send end of interrupt (hardware interrupts)
	if(intr>=0x20&&intr<=0x2f)
	{
		if(intr<0x29)
		{
			outb(0x20,0x20);
		}
		outb(0xa0,0x20);
	}

	return cpu;
}
