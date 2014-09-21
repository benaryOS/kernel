#include <constants.h>

extern size_t printk(const char *,...);

extern void tss_entry_set(uint32_t,uint32_t);

extern void halt(void);

static struct task *current_task=0;
static struct task *first_task=0;

void task_add(struct task *t)
{
	if(first_task)
	{
		t->next=first_task->next;
		first_task->next=t;
	}
	else
	{
		t->next=t;
		first_task=t;
	}
}

struct cpu_state *schedule(struct cpu_state *cpu)
{
	if(current_task)
	{
		current_task->cpu=cpu;
		current_task=current_task->next;
		printk("switching to %d\n",current_task->pid);
		cpu=current_task->cpu;
	}
	else
	{
		if(first_task)
		{
			current_task=first_task;
			cpu=current_task->cpu;
			printk("starting first task\n");
		}
		else
		{
			printk("no tasks\n");
			halt();
		}
	}
	tss_entry_set(1,(uint32_t)cpu);
	return cpu;
}
