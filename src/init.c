#include <constants.h>

extern int printk(const char *,...);
extern int putchar(int);
extern size_t text_pos;

void init(void)
{
	size_t i;
	for(i=0;i<TEXT_HEIGHT*TEXT_WIDTH;i++)
	{
		putchar(' ');
	}
	text_pos=0;
	
	printk("benaryOS booted!\n%c\n%d\n",'b',1234);
}
