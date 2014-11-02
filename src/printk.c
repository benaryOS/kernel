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

extern int putchar(int);
extern size_t strlen(const char *);
extern void com(uint8_t);

size_t printint(int i)
{
	if(!i)
	{
		putchar('0');
		return 1;
	}
	if(i<0)
	{
		putchar('-');
		return printint(-i)+1;
	}
	int j,k;
	for(k=j=0;i;i/=10,k++)
	{
		j*=10;
		j+=i%10;
	}
	for(i=0;i<k;i++)
	{
		putchar('0'+(j%10));
		j/=10;
	}
	return (size_t)i;
}

int printk(const char *format,...)
{
	va_list args;
	va_start(args,format);

	size_t len;
	int i;
	for(len=i=0;i<strlen(format);i++)
	{
		switch(format[i])
		{
			case '%':
				i++;
				switch(format[i])
				{
					case 'd':
					{
						len+=printint(va_arg(args,int));
						break;
					}
					case 'c':
					{
						putchar(va_arg(args,int));
						len++;
						break;
					}
					case 's':
					{
						int j;
						char *str=va_arg(args,char *);
						for(j=0;j<strlen(str);j++,len++)
						{
							putchar(str[j]);
						}
						break;
					}
					case '%':
					{
						putchar('%');
						len++;
						break;
					}
					default:
					{
						continue;
					}
				}
				break;
			default:
				putchar(format[i]);
				com(format[i]);
				len++;
				break;
		}
	}
	va_end(args);
	return len;
}
