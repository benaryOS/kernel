#include <constants.h>

size_t text_pos=0;
char text_color=0x0a;

int putchar(int ch)
{
	*(TEXT_BUFFER+(text_pos*2))=(char)ch;
	*(TEXT_BUFFER+(text_pos*2)+1)=text_color;
	text_pos++;
	return ch;
}
