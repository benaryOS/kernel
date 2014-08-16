#include <constants.h>

void halt(void)
{
	while(1)
	{
		asm volatile("hlt");
	}
}
