#include <constants.h>

extern int printk(const char *,...);
extern int putchar(int);
extern size_t text_pos;

extern void gdt_init(void);
extern void pic_init(void);
extern void pit_init(int);
extern void idt_init(void);
extern void pmm_init(struct multiboot *);

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

	printk("initialise PMM\n");
	pmm_init(mb);

	printk("loading GDT\n");
	gdt_init();

	printk("initialise PIT\n");
	pit_init(100);

	printk("initialise PIC\n");
	pic_init();

	printk("initialise IDT\n");
	idt_init();

	asm volatile("sti");

	printk("benaryOS running\n");
	while(1);
}
