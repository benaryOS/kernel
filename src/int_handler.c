#include <constants.h>

extern int printk(const char *,...);

struct cpu_state *int_handler(struct cpu_state *cpu)
{
	printk("interrupt(%d)\n",cpu->intr);
	return cpu;
}
