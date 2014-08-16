#include <constants.h>

extern int printk(const char *,...);
extern void outb(uint16_t,uint8_t);

extern struct cpu_state *int_exception_handler(struct cpu_state *);

struct cpu_state *int_handler(struct cpu_state *cpu)
{
	struct cpu_state *oldcpu=cpu;
	if(cpu->intr>=0x00&&cpu->intr<0x20)
	{
		cpu=int_exception_handler(cpu);
	}
	else
	{
		printk("interrupt(%d)\n",cpu->intr);
	}
	//send end of interrupt (hardware interrupts)
	if(oldcpu->intr>=0x20&&oldcpu->intr<=0x2f)
	{
		if(oldcpu->intr>=0x28)
		{
			outb(0xa0,0x20);
		}
		outb(0x20,0x20);
	}

	//while(1);
	return cpu;
}
