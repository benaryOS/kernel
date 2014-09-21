#include <constants.h>

extern void *pmm_alloc_block(void);
extern uint32_t pid_get(void);

void task_create_cpu(struct cpu_state *dst,void *entry)
{
	struct cpu_state cpu=
	{
		.eax=0,
		.ebx=0,
		.ecx=0,
		.edx=0,
		.esi=0,
		.edi=0,
		.ebp=0,
		.esp=0,
		.eip=(uint32_t)entry,
		.cs=0,
		.ss=0,
		.eflags=0x202,
	};
	*dst=cpu;
}

struct task *task_create_kernel(void *entry)
{
	struct task *task=(struct task *)pmm_alloc_block();
	task->pid=pid_get();
	char *stack=(char *)pmm_alloc_block();
	struct cpu_state *state=(struct cpu_state *)(stack+4096-sizeof(struct cpu_state));
	task_create_cpu(state,entry);
	state->cs=0x08;
	task->cpu=state;
	return task;
}

struct task *task_create_user(void *entry)
{
	struct task *task=(struct task *)pmm_alloc_block();
	task->pid=pid_get();
	char *stack=(char *)pmm_alloc_block();
	struct cpu_state *state=(struct cpu_state *)(stack+4096-sizeof(struct cpu_state));
	task_create_cpu(state,entry);
	state->cs=0x18|0x03;
	state->ss=0x20|0x03;
	state->esp=(uint32_t)(((char *)pmm_alloc_block())+4096);
	task->cpu=state;
	return task;
}

