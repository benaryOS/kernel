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

extern void outb(uint16_t,uint8_t);

void pic_init(void)
{
	outb(0x20,0x11);//init master pic
	outb(0x21,0x20);//hardware irq get irq numbers 0x20+
	outb(0x21,0x04);//bind on irq 0x04
	outb(0x21,0x01);//"apply"
	  
	outb(0xa0, 0x11);//init slave pic
	outb(0xa1, 0x28);//hardware irq 8+ get numbers 0x28+
	outb(0xa1, 0x02);//bind on irq 0x02
	outb(0xa1, 0x01);//"apply"

	//demask the interrupts
	outb(0x20, 0x0);
	outb(0xa0, 0x0);


	//ALL COMMENTS ARE WRONG. I DON'T KNOW WHAT I'M DOING!
}
