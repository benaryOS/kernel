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

static uint32_t tss[32]={0,0,0x10};

void tss_entry_set(uint32_t i,uint32_t val)
{
	tss[i]=val;
}

uint32_t tss_entry_get(uint32_t i)
{
	return tss[i];
}

static uint64_t gdt[GDT_SIZE]={};

//basically stolen from benaryOS which stole it from lowlevel.eu (=tyndur)
//benaryorg is a real thief!
void gdt_entry(int i,unsigned int base,unsigned int limit,int flags)
{
	uint64_t entry=0;
	entry|= 	limit	&	0xffffLL;
	entry|= (	base	&	0xffffffLL	) << 16;
	entry|= (	flags	&	0xffLL		) << 40;
	entry|= ( (	limit >> 16 )	&	0xfLL	) << 48;
	entry|= ( (	flags >> 8 )	&	0xffLL	) << 52;
	entry|= ( (	base >> 24 )	&	0xffLL	) << 56;
	gdt[i]=entry;
}

void reload_gdt(void)
{
	struct
	{
		uint16_t limit;
		void *pointer;
	}
	__attribute__((packed)) gdtp=
	{
		.limit=GDT_SIZE*8-1,
		.pointer=gdt,
	};
	asm volatile("lgdt %0" : : "m" (gdtp));
	
	asm volatile
	(
		"mov $0x10, %ax\n"
		"mov %ax, %ds\n"
		"mov %ax, %es\n"
		"mov %ax, %fs\n"
		"mov %ax, %gs\n"
		"mov %ax, %ss\n"
		"ljmp $0x8, $.1\n"
		".1:"
	);
}

void gdt_init(void)
{
	//sorry, this is against every (EVERY) coding standard (at most against the 80 char lines) but it is only readable when not split into multiple lines. sorry.
	gdt_entry(0,0,0,0);
	gdt_entry(1,0,0xfffff,GDT_FLAG_SEGMENT|GDT_FLAG_32_BIT|GDT_FLAG_CODESEG|GDT_FLAG_4K_GRAN|GDT_FLAG_PRESENT);
	gdt_entry(2,0,0xfffff,GDT_FLAG_SEGMENT|GDT_FLAG_32_BIT|GDT_FLAG_DATASEG|GDT_FLAG_4K_GRAN|GDT_FLAG_PRESENT);
	gdt_entry(3,0,0xfffff,GDT_FLAG_SEGMENT|GDT_FLAG_32_BIT|GDT_FLAG_CODESEG|GDT_FLAG_4K_GRAN|GDT_FLAG_PRESENT|GDT_FLAG_RING3);
	gdt_entry(4,0,0xfffff,GDT_FLAG_SEGMENT|GDT_FLAG_32_BIT|GDT_FLAG_DATASEG|GDT_FLAG_4K_GRAN|GDT_FLAG_PRESENT|GDT_FLAG_RING3);
	gdt_entry(5,(uint32_t)tss,sizeof(tss),GDT_FLAG_TSS|GDT_FLAG_PRESENT|GDT_FLAG_RING3);

	reload_gdt();

	//load tss
	 asm volatile("ltr %%ax" : : "a" (5 << 3));
}

