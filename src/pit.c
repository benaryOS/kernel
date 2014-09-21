#include <constants.h>

extern void outb(uint16_t,uint8_t);

void pit_init(int f)
{
	int c=1193182/f;
	outb(0x43,0x34);
	outb(0x40,c&0xFF);
	outb(0x40,c>>8);
}

