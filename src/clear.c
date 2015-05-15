#include <header.h>

/*
 * clears the screen
 */
void clear(void)
{
	int i;
	for(i=0;i<TEXT_WIDTH*TEXT_HEIGHT;i++)
	{
		//set to zero
		*((uint16_t *)TEXT+i)=0;
	}
}

