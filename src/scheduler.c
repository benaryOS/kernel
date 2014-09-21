#include <constants.h>

extern size_t printk(const char *,...);

extern void tss_entry_set(uint32_t,uint32_t);

static struct task *current_task=0;

struct cpu_state *schedule(struct cpu_state *cpu)
{
	if(current_task)
	{
		current_task=current_task->next;
		printk("switching to %d\n",current_task->pid);
		cpu=current_task->cpu;
	}
	else
	{
		printk("no tasks\n");
	}
	tss_entry_set(1,(uint32_t)cpu);
	return cpu;
}
