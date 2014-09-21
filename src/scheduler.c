#include <constants.h>

extern size_t printk(const char *,...);

static struct task *current_task=0;

struct cpu_state *schedule(struct cpu_state *cpu)
{
	if(current_task)
	{
		current_task=current_task->next;
		printk("switching to %d\n",current_task->pid);
		return cpu;
	}
	else
	{
		printk("no tasks\n");
		return cpu;
	}
}
