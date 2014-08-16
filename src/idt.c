#include <constants.h>



static struct idt_desc idt[IDT_SIZE]={};

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
