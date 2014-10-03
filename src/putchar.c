/*
 * Copyright 2014 benaryorg (benaryorg@benaryos.org)
 *
 * This file is part of benaryOS.
 *
 * benaryOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * benaryOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with benaryOS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
