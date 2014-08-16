#include <constants.h>

extern void *memcpy(void *,const void *,size_t);

size_t text_pos=0;
static char text_color=0x0a;

int putchar(int ch)
{
	switch(ch)
	{
		case '\r':
			text_pos-=text_pos%TEXT_WIDTH;
			break;
		case '\n':
			text_pos+=TEXT_WIDTH-(text_pos%TEXT_WIDTH);
			break;
		default:
			*(TEXT_BUFFER+(text_pos*2))=(char)ch;
			*(TEXT_BUFFER+(text_pos*2)+1)=text_color;
			text_pos++;
			break;
	}
	if(text_pos>=TEXT_WIDTH*TEXT_HEIGHT)
	{
		memcpy(TEXT_BUFFER,TEXT_BUFFER,TEXT_WIDTH*(TEXT_HEIGHT-1));
		text_pos=TEXT_WIDTH*(TEXT_HEIGHT-1);
	}
	return ch;
}
