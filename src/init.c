#include <constants.h>

extern int printk(const char *,...);

void init(void)
{
	printk("benaryOS booted!\n");
}
