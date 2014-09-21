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
