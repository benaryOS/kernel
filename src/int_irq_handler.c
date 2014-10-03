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

extern int printk(const char *format,...);

extern struct cpu_state *schedule(struct cpu_state *);

extern struct task *current_task;

struct cpu_state *int_irq_handler(struct cpu_state *cpu)
{
	switch(cpu->intr-0x20)
	{
		case 0x00:
			cpu=schedule(cpu);
			break;
		case 0x01:
			printk("keyboard\n");
			break;
		case 0x02:
			printk("second PIC\n");
			break;
		case 0x03:
			printk("RS-232 port 2/4\n");
			break;
		case 0x04:
			printk("RS-232 Port 1/3\n");
			break;
		case 0x05:
			printk("LPT 2\n");
			break;
		case 0x06:
			printk("floppy disk controller\n");
			break;
		case 0x07:
			printk("LPT 1/spurious interrupt\n");
			break;
		case 0x08:
			printk("RTC\n");
			break;
		case 0x09:
			printk("free IRQ - should never happen\n");
			break;
		case 0x0a:
			printk("fourth ATA/ATAPI/(E)IDE\n");
			break;
		case 0x0b:
			printk("third ATA/ATAPI/(E)IDE\n");
			break;
		case 0x0c:
			printk("mouse\n");
			break;
		case 0x0d:
			printk("FPU\n");
			break;
		case 0x0e:
			printk("first ATA/ATAPI/(E)IDE\n");
			break;
		case 0x0f:
			printk("second ATA/ATAPI/(E)IDE/spurious interrupt\n");
			break;
		default:
			printk("irq (%d)\n",cpu->intr);
			break;
	}

	return cpu;
}
