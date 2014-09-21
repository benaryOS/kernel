#include <constants.h>

extern size_t printk(const char *,...);

struct cpu_state *schedule(struct cpu_state *cpu)
{
	printk("timer\n");
	return cpu;
}
