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

extern int putchar(int);
extern size_t printk(const char *,...);

struct cpu_state *int_syscall_handler(struct cpu_state *cpu)
{
	switch(cpu->eax)
	{
		case SYSCALL_PUTCHAR:
			putchar(cpu->ebx);
			break;
		default:
			printk("unknown syscall(%d)\n",cpu->eax);
			break;
	}

	return cpu;
}
