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

extern const void intr_stub_0(void);
extern const void intr_stub_1(void);
extern const void intr_stub_2(void);
extern const void intr_stub_3(void);
extern const void intr_stub_4(void);
extern const void intr_stub_5(void);
extern const void intr_stub_6(void);
extern const void intr_stub_7(void);
extern const void intr_stub_8(void);
extern const void intr_stub_9(void);
extern const void intr_stub_10(void);
extern const void intr_stub_11(void);
extern const void intr_stub_12(void);
extern const void intr_stub_13(void);
extern const void intr_stub_14(void);
extern const void intr_stub_15(void);
extern const void intr_stub_16(void);
extern const void intr_stub_17(void);
extern const void intr_stub_18(void);

extern const void intr_stub_32(void);
extern const void intr_stub_33(void);
extern const void intr_stub_34(void);
extern const void intr_stub_35(void);
extern const void intr_stub_36(void);
extern const void intr_stub_37(void);
extern const void intr_stub_38(void);
extern const void intr_stub_39(void);
extern const void intr_stub_40(void);
extern const void intr_stub_41(void);
extern const void intr_stub_42(void);
extern const void intr_stub_43(void);
extern const void intr_stub_44(void);
extern const void intr_stub_45(void);
extern const void intr_stub_46(void);
extern const void intr_stub_47(void);

extern const void intr_stub_48(void);

static struct idt_desc idt[IDT_SIZE]={};

void reload_idt(void)
{
	struct
	{
		uint16_t limit;
		void *pointer;
	}
	__attribute__((packed)) idtp=
	{
		.limit=IDT_SIZE*8-1,
		.pointer=idt,
	};
	asm volatile("lidt %0" : : "m" (idtp));
	
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

void idt_entry_set(int intr,uint16_t selector,void *handler,int dpl,int type)
{
	struct idt_desc entry=
	{
		((uint32_t)handler)&0xFFFF,
		selector,
		0,
		0x80|((dpl&3)<<5)|type,
		(((uint32_t)handler)>>16)&0xFFFF
	};
	idt[intr]=entry;
}

void idt_init(void)
{
	//exceptions
	idt_entry_set(0 ,0x08,intr_stub_0 ,0,IDT_TRAP_GATE);
	idt_entry_set(1 ,0x08,intr_stub_1 ,0,IDT_TRAP_GATE);
	idt_entry_set(2 ,0x08,intr_stub_2 ,0,IDT_TRAP_GATE);
	idt_entry_set(3 ,0x08,intr_stub_3 ,0,IDT_TRAP_GATE);
	idt_entry_set(4 ,0x08,intr_stub_4 ,0,IDT_TRAP_GATE);
	idt_entry_set(5 ,0x08,intr_stub_5 ,0,IDT_TRAP_GATE);
	idt_entry_set(6 ,0x08,intr_stub_6 ,0,IDT_TRAP_GATE);
	idt_entry_set(7 ,0x08,intr_stub_7 ,0,IDT_TRAP_GATE);
	idt_entry_set(8 ,0x08,intr_stub_8 ,0,IDT_TRAP_GATE);
	idt_entry_set(9 ,0x08,intr_stub_9 ,0,IDT_TRAP_GATE);
	idt_entry_set(10,0x08,intr_stub_10,0,IDT_TRAP_GATE);
	idt_entry_set(11,0x08,intr_stub_11,0,IDT_TRAP_GATE);
	idt_entry_set(12,0x08,intr_stub_12,0,IDT_TRAP_GATE);
	idt_entry_set(13,0x08,intr_stub_13,0,IDT_TRAP_GATE);
	idt_entry_set(14,0x08,intr_stub_14,0,IDT_TRAP_GATE);
	idt_entry_set(15,0x08,intr_stub_15,0,IDT_TRAP_GATE);
	idt_entry_set(16,0x08,intr_stub_16,0,IDT_TRAP_GATE);
	idt_entry_set(17,0x08,intr_stub_17,0,IDT_TRAP_GATE);
	idt_entry_set(18,0x08,intr_stub_18,0,IDT_TRAP_GATE);

	//hardware interrupts
	idt_entry_set(32,0x08,intr_stub_32,0,IDT_INTERRUPT_GATE);
	idt_entry_set(33,0x08,intr_stub_33,0,IDT_TRAP_GATE);
	idt_entry_set(34,0x08,intr_stub_34,0,IDT_TRAP_GATE);
	idt_entry_set(35,0x08,intr_stub_35,0,IDT_TRAP_GATE);
	idt_entry_set(36,0x08,intr_stub_36,0,IDT_TRAP_GATE);
	idt_entry_set(37,0x08,intr_stub_37,0,IDT_TRAP_GATE);
	idt_entry_set(38,0x08,intr_stub_38,0,IDT_TRAP_GATE);
	idt_entry_set(39,0x08,intr_stub_39,0,IDT_TRAP_GATE);
	idt_entry_set(40,0x08,intr_stub_40,0,IDT_TRAP_GATE);
	idt_entry_set(41,0x08,intr_stub_41,0,IDT_TRAP_GATE);
	idt_entry_set(42,0x08,intr_stub_42,0,IDT_TRAP_GATE);
	idt_entry_set(43,0x08,intr_stub_43,0,IDT_TRAP_GATE);
	idt_entry_set(44,0x08,intr_stub_44,0,IDT_TRAP_GATE);
	idt_entry_set(45,0x08,intr_stub_45,0,IDT_TRAP_GATE);
	idt_entry_set(46,0x08,intr_stub_46,0,IDT_TRAP_GATE);
	idt_entry_set(47,0x08,intr_stub_47,0,IDT_TRAP_GATE);

	//syscall
	idt_entry_set(48,0x08,intr_stub_48,0,IDT_TRAP_GATE);
	
	reload_idt();
}

