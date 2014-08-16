#include <constants.h>

extern int printk(const char *,...);
extern int putchar(int);
extern size_t text_pos;

extern void gdt_init(void);
extern void pic_init(void);

void init(void)
{
	size_t i;
	for(i=0;i<TEXT_HEIGHT*TEXT_WIDTH;i++)
	{
		putchar(' ');
	}
	text_pos=0;
	
	printk("benaryOS booted\n");

	printk("loading GDT\n");
	gdt_init();

	printk("initialise PIC\n");
	pic_init();

	while(1);
}
