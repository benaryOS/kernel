#include <constants.h>

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
