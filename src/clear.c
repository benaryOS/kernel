#include <header.h>

/*
 * clears the screen
 */
void clear(void)
{
	int i;
	for(i=0;i<80*40;i++)
	{
		//set to zero
		*((uint16_t *)TEXTBUFFER+i)=0;
	}
}

