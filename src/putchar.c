#include <constants.h>

extern void *memcpy(void *,const void *,size_t);
extern void outb(uint16_t,uint8_t);

size_t text_pos=0;
char text_color=0x0a;

void update_cursor_pos(void)
{
	outb(0x3D4,14);
	outb(0x3D5,text_pos>>8);
	outb(0x3D4,15);
	outb(0x3D5,text_pos);
}

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
		memcpy(TEXT_BUFFER,TEXT_BUFFER+(TEXT_WIDTH*2),TEXT_WIDTH*(TEXT_HEIGHT-1)*2);
		size_t n;
		for(n=0;n<TEXT_WIDTH;n++)
		{
			*(TEXT_BUFFER+TEXT_WIDTH*(TEXT_HEIGHT-1)*2+(n*2))=0;
			*(TEXT_BUFFER+TEXT_WIDTH*(TEXT_HEIGHT-1)*2+(n*2+1))=text_color;
		}
		text_pos=TEXT_WIDTH*(TEXT_HEIGHT-1);
	}

	update_cursor_pos();

	return ch;
}
