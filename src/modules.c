#include <constants.h>

extern void *memcpy(void *,void *,size_t);

extern struct task *task_create_kernel(void *);
extern void task_add(struct task *);

void elf_load(void *,size_t);

void modules_init(struct multiboot *mb)
{
	if(mb->mbs_mods_count!=1)
	{
		return;
	}
	struct mb_module *modules=mb->mbs_mods_addr;
	size_t i;
	for(i=0;i<mb->mbs_mods_count;i++)
	{
		elf_load(modules[i].start,modules[i].end-modules[i].start);
	}
}
