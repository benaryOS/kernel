#include <header.h>

static uint16_t cur=0;
static uint16_t colour=0x0a;

int putchar(int ch)
{
	if(ch^(ch&0xff))
	{
		return EOF;
	}
	if(cur>=TEXT_WIDTH*TEXT_HEIGHT)
	{
		//TODO:scroll
		return EOF;
	}

	//TODO:check for special characters

	((uint16_t *)TEXT)[cur++]=(colour<<8)|ch;
	return ch;
}

