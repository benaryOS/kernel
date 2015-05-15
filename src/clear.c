#include <header.h>

/*
 * clears the screen
 */
void clear(void)
{
	short int *txt=TEXTBUFFER;
	int i;
	for(i=0;i<80*40;i++)
	{
		//set to zero
		txt[i]=0;
	}
}

