#include <constants.h>

size_t text_pos=0;
char text_color=0x0a;

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
	return ch;
}
