#include <constants.h>

extern int printk(const char *,...);
extern int putchar(int);
extern size_t text_pos;

extern void modules_init(struct multiboot *);
extern void paging_init(void);
extern void gdt_init(void);
extern void pic_init(void);
extern void pit_init(int);
extern void idt_init(void);
extern void pmm_init(struct multiboot *);

extern struct task *task_create_kernel(void *);
extern struct task *task_create_user(void *);

extern void task_add(struct task *);

void init(struct multiboot *mb)
{
	size_t i;
	for(i=0;i<TEXT_HEIGHT*TEXT_WIDTH;i++)
	{
		putchar(' ');
	}
	text_pos=0;
	
	printk("benaryOS booted");
	if(mb->mbs_cmdline)
	{
		printk(" with cmdline \"%s\"",(char *)mb->mbs_cmdline);
	}
	putchar('\n');

	//Physical Memory Management
	printk("initialise PMM\n");
	pmm_init(mb);

	//Paging
	printk("initialise Paging\n");
	paging_init();

	//Modules
	printk("loading modules(%d)\n",mb->mbs_mods_count);
	modules_init(mb);

	//Global Descriptor Table
	printk("loading GDT\n");
	gdt_init();

	//Programmable Interrupt Timer
	printk("initialise PIT\n");
	pit_init(100);

	//Programmable Interrupt Controller
	printk("initialise PIC\n");
	pic_init();

	//Interrupt Descriptor Table
	printk("initialise IDT\n");
	idt_init();

	printk("benaryOS running\n");
	printk("starting first task now\n");
	asm volatile("sti");

	//this will forget our thread
	asm volatile("int $0x20");
}
