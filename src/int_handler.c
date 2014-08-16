#include <constants.h>

extern int printk(const char *,...);
extern void outb(uint16_t,uint8_t);

struct cpu_state *int_handler(struct cpu_state *cpu)
{
	printk("interrupt(%d)\n",cpu->intr);

	//send end of interrupt (hardware interrupts)
	if(cpu->intr>=0x20&&cpu->intr<=0x2f)
	{
		if(cpu->intr>=0x28)
		{
			outb(0xa0,0x20);
		}
		outb(0x20,0x20);
	}

	//while(1);
	return cpu;
}
