#include <constants.h>

extern void *memcpy(void *,void *,size_t);

extern struct task *task_create_kernel(void *);
extern void task_add(struct task *);

void modules_init(struct multiboot *mb)
{
	if(mb->mbs_mods_count!=1)
	{
		return;
	}
	void *load_addr=(void *)0x200000;
	struct mb_module *modules=mb->mbs_mods_addr;
	memcpy(load_addr,(void *)modules[0].start,modules[0].end-modules[0].start);
	struct task *t=task_create_kernel(load_addr);
	task_add(t);
}
