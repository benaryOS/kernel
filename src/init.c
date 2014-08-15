#include <constants.h>

void init(void)
{
	char hw[]="Hello World!";
	int i;
	char *video=TEXT_BUFFER;
	for(i=0;hw[i]!='\0';i++)
	{
		video[i*2]=hw[i];
		video[i*2+1]=0x07;
	}
}
